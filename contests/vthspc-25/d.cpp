#include <iostream>
#include <vector>

const int N = 1e5;

std::vector<int> a[N];
int c[N];

void dfs(int i, int p, int d){
	for(int j : a[i]) if(j != p) dfs(j, i, d+1);
	++c[d];
}

int main(){
	int n; std::cin >> n;

	for(int i=1; i<n; ++i){
		int u, v; std::cin >> u >> v;
		a[u].push_back(v);
		a[v].push_back(u);
	}

	dfs(0, 0, 0);

	int best = 0, ct = c[0];
	for(int i=1; i<n; ++i) if(c[i] > ct) best = i, ct = c[i];
	std::cout << best << '\n';
}
