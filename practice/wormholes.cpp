// https://dmoj.ca/problem/dmopc18c4p5

#include <algorithm>
#include <iostream>
#include <vector>
#include <array>

using LL = long long;

int main(){
	int n, k; std::cin >> n >> k;

	int m[k], *mp = m; for(int i=0; i<k; ++i) std::cin >> m[i];
	std::sort(m, m+k);

	std::vector<std::array<int, 3>> adj[n];

	for(int i=1; i<n; ++i){
		int a, b, t; std::cin >> a >> b >> t, --a, --b;

		int massive = 0;
		if(mp != m+k && i == *mp) massive = 1, ++mp;

		adj[a].push_back({b, t, massive}), adj[b].push_back({a, t, massive});
	}

	bool vis[n] = {1};
	// longest path/loop from n through children
	LL longest[n] = {}, loop[n] = {};

	std::vector<std::array<int, 3>> children[n];

	// first dfs to determine longest + loop
	std::vector<int> dfs; dfs.push_back(0);

	while(dfs.size()){
		int t = dfs.back();

		if(adj[t].size()){
			auto x = adj[t].back(); adj[t].pop_back();

			if(!vis[x[0]]){
				vis[x[0]] = 1;
				children[t].push_back({x[0], x[1], x[2]});
				dfs.push_back(x[0]);
			}
		}else{
			dfs.pop_back();

			// accumulate from children

			for(auto &[index, time, large] : children[t]) if(large)
				loop[t] += time*2 + loop[index];

			LL consider[children[t].size()] = {};

			int run = 0;
			for(int i=0; i<children[t].size(); ++i){
				consider[i] += run;
				const auto x = children[t][i];
				if(x[2]) run += x[1]*2 + loop[x[0]];
			}

			run = 0;
			for(int i=children[t].size()-1; i+1; --i){
				consider[i] += run;
				const auto x = children[t][i];
				if(x[2]) run += x[1]*2 + loop[x[0]];
			}

			for(int i=0; i<children[t].size(); ++i)
				longest[t] = std::max(
						longest[t],
						consider[i]+longest[children[t][i][0]]+(LL)children[t][i][1]);
		}
	}

	// still need to compute final paths
	// need to efficiently compute for each node which of the following
	// is optimal:
	//     1. path rooted at that node
	//     2. path whose endpoints are some children of it
	// 1) is already computed but 2) is probably harder
	//
	// oh this is probably possible because of the observation:
	// for some node n with children c0 c1 etc. if creating a path
	// through n such that its endpoints are on two different child
	// subtrees, the sum of lengths will be longest[] of the two
	// subtrees with endpoints and the loop[] of all others; therefore
	// we can keep track of longest[]-loop[] for each subtree and choose
	// the optimal delta i think

	dfs.push_back(0);

	// loops above node
	LL up[n] = {}, best = 0;

	while(dfs.size()){
		int t = dfs.back(); dfs.pop_back();

		// path ending at t
		best = std::max(best, longest[t] + up[t]);

		// path with endpoints in seperate subtrees of t
		LL total = 0, delta[2] = {};

		for(const auto &[i, time, l] : children[t]){
			LL d = time + longest[i];
			if(l) total += time*2 + loop[i],
				d -= time*2 + loop[i];
			if(d > delta[0]){
				delta[0] = d;
				if(d > delta[1]){
					delta[0] = delta[1];
					delta[1] = d;
				}
			}
		}

		// wait this has weird behavior when all deltas are negative
		// surely that still works because it represents a path where
		// all segments are loops ?
		best = std::max(best, up[t] + delta[1] + total);

		for(const auto &[i, time, l] : children[t]){
			if(l) up[i] = up[t] + time*2;
			dfs.push_back(i);
		}
	}

	std::cout << best << '\n';
}
