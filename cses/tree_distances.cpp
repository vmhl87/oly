#include <iostream>
#include <stack>
#include <cmath>

int main(){
	int n; std::cin >> n;

	std::stack<int> adj[n], bdj[n];

	for(int i=1; i<n; ++i){
		int a, b; std::cin >> a >> b, --a, --b;

		adj[a].push(b), adj[b].push(a);
	}

	bool vis[n] = {};
	std::stack<int> dfs; dfs.push(0), vis[0] = 1;

	int height[n] = {}, ext[n] = {};

	while(dfs.size()){
		int t = dfs.top();

		if(adj[t].size()){
			int next = adj[t].top(); adj[t].pop();

			if(!vis[next]){
				vis[next] = 1;
				dfs.push(next), bdj[t].push(next);

				ext[next] = std::max(ext[next], height[t]+1);
				ext[next] = std::max(ext[next], ext[t]+1);
			}

		}else{
			dfs.pop();

			if(dfs.size()) height[dfs.top()] = std::max(
					height[dfs.top()], height[t]+1
				);
		}
	}

	dfs.push(0);
	for(int i=0; i<n; ++i) height[i] = 0;

	while(dfs.size()){
		int t = dfs.top();

		if(bdj[t].size()){
			int next = bdj[t].top(); bdj[t].pop();

			dfs.push(next);

			ext[next] = std::max(ext[next], height[t]+1);
			ext[next] = std::max(ext[next], ext[t]+1);

		}else{
			dfs.pop();

			if(dfs.size()) height[dfs.top()] = std::max(
					height[dfs.top()], height[t]+1
				);
		}
	}

	for(int i=0; i<n; ++i)
		std::cout << std::max(ext[i], height[i]) << " \n"[i==n-1];
}
