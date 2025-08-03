#include <iostream>
#include <vector>

const int N = 1000;

std::vector<int> adj[N];
bool v[N], r[N];
int d1[N], d2[N];

void dfs(int i){
	r[i] = 1;
	for(int x : adj[i]) if(!v[x] && !r[x]) dfs(x);
}

void test(){
	int n, m, x, y; std::cin >> n >> m >> x >> y, --x, --y;

	for(int i=0; i<n; ++i){
		adj[i].clear();
		d1[i] = -1, d2[i] = -1;
		v[i] = 0;
	}

	for(int i=0; i<m; ++i){
		int u, v; std::cin >> u >> v;
		adj[--u].push_back(--v);
		adj[v].push_back(u);
	}

	for(; x != y;){
		std::cout << x+1 << ' ';
		if(x == 1e9) break;
		v[x] = 1;

		for(int i=0; i<n; ++i) r[i] = 0;
		dfs(y);

		int b = 1e9;
		for(int i : adj[x]) if(!v[i] && r[i] && i < b) b = i;
		x = b;
	}

	std::cout << y+1 << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
