#include <iostream>
#include <vector>

using ll = long long;

std::vector<int> adj[200000];
int deg[200000], under[200000];
bool vis[200000];
ll res = 0;

void dfs(int i, int p){
	vis[i] = 1;

	for(int x : adj[i]) if(x != p && (deg[x] == 2 || deg[x] == 3)){
		dfs(x, i), under[i] += under[x];
	}

	if(deg[i] == 2){
		for(int x : adj[i]) if(x != p && deg[x] == 3)
			res += under[x];
		under[i] = 1;
	}else{
		ll part = 0;
		for(int x : adj[i]) if(x != p && (deg[x] == 2 || deg[x] == 3))
			res += under[x]*part, part += under[x];
	}
}

int main(){
	int n; std::cin >> n;
	for(int i=1; i<n; ++i){
		int a, b; std::cin >> a >> b;
		adj[--a].push_back(--b);
		adj[b].push_back(a);
		++deg[a], ++deg[b];
	}

	for(int i=0; i<n; ++i)
		if(deg[i] == 2 && !vis[i])
			dfs(i, i);

	std::cout << res << '\n';
}
