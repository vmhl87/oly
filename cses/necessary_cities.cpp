#include <iostream>
#include <vector>

std::vector<int> adj[100000], res;
bool vis[100000];

int end[100000], dep[100000], now;

void dfs(int i, int p){
	vis[i] = 1;

	int count = i != p, diff = 0;
	for(int x : adj[i]) if(x != p)
		if(!vis[x]){
			int t = now; now = 0;
			dep[x] = dep[i] + 1;
			dfs(x, i);
			now -= end[i], end[i] = 0;
			if(!now) ++count;
			now += t;
		}else if(dep[x] < dep[i]){
			++end[x];
			++diff;
		}

	now -= end[i];

	if(count > 1) res.push_back(i);
	
	now += diff;
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
