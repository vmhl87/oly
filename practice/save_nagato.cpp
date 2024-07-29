// https://dmoj.ca/problem/dmopc14c4p6

#include <iostream>
#include <vector>
#include <stack>

int main(){
	int n; std::cin >> n;

	std::vector<int> adj[n];

	for(int i=1; i<n; ++i){
		int a, b; std::cin >> a >> b, --a, --b;

		adj[a].push_back(b), adj[b].push_back(a);
	}

	int parent[n] = {-1}, down[n] = {};
	std::vector<int> child[n];
	bool vis[n] = {1};

	std::vector<int> dfs; dfs.push_back(0);

	while(dfs.size()){
		int t = dfs.back();

		if(adj[t].size()){
			int x = adj[t].back(); adj[t].pop_back();

			if(!vis[x])
				vis[x] = 1, child[t].push_back(x), dfs.push_back(x), parent[x] = t;
		}else{
			dfs.pop_back();

			if(parent[t]+1)
				down[parent[t]] = std::max(down[parent[t]], down[t]+1);
		}
	}

	int up[n] = {};

	dfs.push_back(0);

	while(dfs.size()){
		int t = dfs.back(); dfs.pop_back();

		int best = 0;
		for(auto i=child[t].begin(); i!=child[t].end(); ++i){
			up[*i] = std::max(up[*i], up[t]+1);
			up[*i] = std::max(up[*i], best+1);
			best = std::max(best, down[*i]+1);
		}

		best = 0;
		for(auto i=child[t].rbegin(); i!=child[t].rend(); ++i){
			up[*i] = std::max(up[*i], best+1);
			best = std::max(best, down[*i]+1);
		}

		for(int x : child[t]) dfs.push_back(x);
	}

	for(int i=0; i<n; ++i) std::cout << 1+std::max(up[i], down[i]) << '\n';
}
