#include <iostream>
#include <vector>
#include <array>

const int N = 2e5;

std::vector<int> adj[N], up[N];
int a[N], ;

void dfs(int i, int j){
}

int main(){
	int n, q; std::cin >> n >> q;
	for(int i=0; i<n; ++i) std::cin >> a[i];

	for(int i=1; i<n; ++i){
		int x, y; std::cin >> x >> y;
		adj[--x].push_back(--y);
		adj[y].push_back(x);
	}

	dfs(0, 0);
}
