#include <iostream>
#include <vector>
#include <array>

using ll = long long;

std::vector<std::array<int, 2>> adj[200000];

ll depth[200000];
bool vis[200000];

void dfs(int i){
	vis[i] = 1;
	for(const auto &[x, w] : adj[i]) if(!vis[x]){
		depth[x] = depth[i] + w;
		dfs(x);
	}
}

int main(){
	int n, m; std::cin >> n >> m;
	while(m--){
		int u, v, w; std::cin >> u >> v >> w;
		--u, --v;
		adj[u].push_back({v, w});
		adj[v].push_back({u, -w});
	}

	for(int i=0; i<n; ++i){
		if(!vis[i]) dfs(i);
		std::cout << depth[i] << " \n"[i==n-1];
	}
}
