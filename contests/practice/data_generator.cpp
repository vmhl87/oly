// https://dmoj.ca/problem/noi03p4

#include <iostream>
#include <vector>
#include <array>

using LL = long long;

std::vector<int> *child;
LL *cost, *down, *up, (*all)[3];
std::vector<std::array<int, 2>> *adj;

void dfs(int i, int p){
	for(const auto &[x, t] : adj[i]) if(x != p){
		cost[x] = t, child[i].push_back(x);
		dfs(x, i);
	}

	if(p+1) down[p] = std::max(down[p], down[i]+cost[i]);
}

void addto(int i, LL val){
	if(val > all[i][0]){
		all[i][0] = val;
		if(val > all[i][1]){
			all[i][0] = all[i][1];
			all[i][1] = val;
			if(val > all[i][2]){
				all[i][1] = all[i][2];
				all[i][2] = val;
			}
		}
	}
}

void dfs2(int t, int p){
	addto(t, up[t]);

	LL best = 0;
	for(auto x = child[t].begin(); x != child[t].end(); ++x){
		addto(t, down[*x]+cost[*x]);

		up[*x] = std::max(up[*x], up[t]+cost[*x]);
		up[*x] = std::max(up[*x], best+cost[*x]);

		best = std::max(best, down[*x]+cost[*x]);
	}

	best = 0;
	for(auto x = child[t].rbegin(); x != child[t].rend(); ++x){
		up[*x] = std::max(up[*x], best+cost[*x]);

		best = std::max(best, down[*x]+cost[*x]);
	}

	for(int x : child[t]) dfs2(x, t);
}

int main(){
	int n; std::cin >> n >> n, ++n; // redundant input lmao
	
	std::vector<std::array<int, 2>> _adj[n]; adj = _adj;

	for(int i=1; i<n; ++i){
		int a, b, t; std::cin >> a >> b >> t, --a, --b;

		adj[a].push_back({b, t}), adj[b].push_back({a, t});
	}

	LL _down[n] = {}, _cost[n];
	std::vector<int> _child[n];

	down = _down, cost = _cost, child = _child;

	dfs(0, -1);

	LL _up[n] = {}, _all[n][3]; all = _all, up = _up;
	for(int i=0; i<n*3; ++i) all[i/3][i%3] = 0;

	dfs2(0, -1);

	LL fin = 0;

	for(int i=0; i<n; ++i){
		fin = std::max(fin, all[i][2]+all[i][1]*2+all[i][0]);
	}

	std::cout << fin << '\n';
}
