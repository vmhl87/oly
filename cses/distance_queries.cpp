// Distance Queries  -  https://cses.fi/problemset/task/1135/
// Literally just binlift bash

#include <iostream>
#include <stack>

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int n, q; std::cin >> n >> q;

	std::stack<int> adj[n];

	for(int i=1; i<n; ++i){
		int a, b; std::cin >> a >> b, --a, --b;

		adj[a].push(b), adj[b].push(a);
	}

	// jump, parent, depth
	int j[n], p[n], depth[n] = {};
	std::stack<int> dfs;

	// repurpose depth arr as visited
	dfs.push(0), j[0] = 0, depth[0] = 1;

	while(dfs.size()){
		int t = dfs.top();

		if(adj[t].size()){
			int next = adj[t].top(); adj[t].pop();

			if(!depth[next]){
				depth[next] = depth[t] + 1;

				// skew binary tree for jump patterns [pretty standard]
				if(depth[t] + depth[j[j[t]]] == depth[j[t]]*2)
					j[next] = j[j[t]];
				else j[next] = t;

				p[next] = t;

				dfs.push(next);
			}
		}else dfs.pop();
	}

	while(q--){
		int a, b; std::cin >> a >> b, --a, --b;

		if(depth[a] < depth[b]) std::swap(a, b);

		int res = depth[a] - depth[b], old = depth[b];

		// balance depths
		while(depth[a] > depth[b]){
			if(depth[j[a]] < depth[b]) a = p[a];
			else a = j[a];
		}

		// search for lca
		while(a != b){
			if(j[a] == j[b]) a = p[a], b = p[b];
			else a = j[a], b = j[b];
		}

		std::cout << res + (old - depth[a])*2 << '\n';
	}
}
