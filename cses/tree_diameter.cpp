#include <iostream>
#include <stack>

int main(){
	int n; std::cin >> n;

	std::stack<int> adj[n];

	for(int i=1; i<n; ++i){
		int a, b; std::cin >> a >> b, --a, --b;

		adj[a].push(b), adj[b].push(a);
	}

	std::stack<int> dfs; dfs.push(0);
	bool vis[n] = {};

	while(dfs.size()){
		int t = dfs.top();

		if(adj[t].size()){
			int next = adj[t].top(); adj[t].pop();

			if(!vis[next]) dfs.push(next), vis[next] = 1;

		}else dfs.pop();
	}
}
