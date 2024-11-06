#include <iostream>
#include <vector>

std::vector<int> adj[100000], res;
bool vis[100000];

int end[100000], now;

void dfs(int i, int p){
	vis[i] = 1;

	int count = 0, total = i != p, diff = 0;
	for(int x : adj[i]) if(x != p)
		if(!vis[x]){
			int t = now; now = 0;
			dfs(x, i), ++total;
			now -= end[i], end[i] = 0;
			if(!now) ++count;
			now += t;
		}else{
			++end[x];
			++now;
		}

	now -= end[i];

	if(count && total > 1) res.push_back(i);
}

int main(){
	int n, m; std::cin >> n >> m;
	while(m--){
		int a, b; std::cin >> a >> b;
		adj[--a].push_back(--b);
		adj[b].push_back(a);
	}

	dfs(0, 0);

	std::cout << res.size() << '\n';
	for(int i : res) std::cout << i+1 << ' ';
	std::cout << '\n';
}
