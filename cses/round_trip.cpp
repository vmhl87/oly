// Round Trip  -  https://cses.fi/problemset/task/1669/
//
// Observe that every cycle of size 3 or more corresponds
// to a valid route and vice versa

#include <iostream>
#include <stack>

int main(){
	int n, m; std::cin >> n >> m;

	std::stack<int> adj[n];

	for(int i=0; i<m; ++i){
		int a, b; std::cin >> a >> b, --a, --b;

		adj[a].push(b), adj[b].push(a);
	}

	std::stack<int> dfs;
	int depth[n] = {};

	// graph not guaranteed connected
	for(int i=0; i<n; ++i) if(!depth[i]){
		dfs.push(i), depth[i] = 1;

		while(dfs.size()){
			int t = dfs.top();

			if(adj[t].size()){
				int x = adj[t].top(); adj[t].pop();

				// find back edges and retrieve path; this is guaranteed
				// to find a valid cycle if exists
				if(depth[x]){
					if(depth[x] < depth[t]-1){
						std::stack<int> rev;
						while(dfs.top() != x) rev.push(dfs.top()), dfs.pop();
						std::cout << rev.size()+2 << '\n' << x+1 << ' ';
						while(rev.size()) std::cout << rev.top()+1 << ' ', rev.pop();
						std::cout << x+1 << '\n';
						return 0;
					}
				}else dfs.push(x), depth[x] = depth[t]+1;
			}else dfs.pop();
		}
	}

	std::cout << "IMPOSSIBLE\n";
}
