#include <iostream>
#include <stack>
#include <set>

int main(){
	int n; std::cin >> n;

	int col[n];
	std::set<int> sub[n];
	std::stack<int> adj[n];

	for(int i=0; i<n; ++i) std::cin >> col[i], sub[i].insert(col[i]);

	for(int i=1; i<n; ++i){
		int a, b; std::cin >> a >> b;
		adj[a-1].push(b-1);
		adj[b-1].push(a-1);
	}

	int parent[n];
	bool vis[n] = {};
	std::stack<int> dfs; dfs.push(0);

	while(dfs.size()){
		int c = dfs.top();
		vis[c] = 1;

		if(adj[c].size()){
			if(!vis[adj[c].top()]) dfs.push(adj[c].top());
			adj[c].pop();
		}else{
			dfs.pop();
			if(dfs.size()) parent[c] = dfs.top();
		}
	}

	for(int i=1; i<n; ++i){
		int p = i;

		while(p != 0){
			p = parent[p];
			if(sub[p].count(col[i])) break;
			sub[p].insert(col[i]);
		}
	}

	for(int i=0; i<n; ++i){
		if(i) std::cout << ' ';
		
		std::cout << sub[i].size();
	}

	std::cout << '\n';
}
