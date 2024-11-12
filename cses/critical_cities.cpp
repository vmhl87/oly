#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

const int maxn = 1e5;

std::vector<int> adj[maxn], bdj[maxn];;
bool vis[maxn], done[maxn];
int rem[maxn];

void dfs(int i){
	vis[i] = 1;
	for(int x : adj[i])
		if(!vis[x]) dfs(x);
}

int main(){
	int n, m; std::cin >> n >> m;
	while(m--){
		int a, b; std::cin >> a >> b;
		adj[--a].push_back(--b);
		bdj[b].push_back(a);
	}

	dfs(0);

	std::queue<int> bfs;
	bfs.push(n-1);

	std::vector<int> res;
	int now = 0;

	while(bfs.size()){
		int t = bfs.front(); bfs.pop();

		done[t] = 1;

		if(!(now -= rem[t])) res.push_back(t+1);

		for(int x : bdj[t]){
			if(vis[x]) bfs.push(x);
			if(!done[x]) ++rem[x], ++now, vis[x] = 0;
		}
	}

	std::cout << res.size() << '\n';
	std::sort(res.begin(), res.end());
	for(int x : res) std::cout << x << ' ';
	std::cout << '\n';
}
