#include <iostream>
#include <vector>

const int maxn = 2e5;

std::vector<int> adj[maxn];
int jmp[19][maxn], dep[maxn];

void dfs(int i, int p){
	for(int x : adj[i]) if(x != p){
		jmp[0][x] = i, dep[x] = dep[i]+1;
		dfs(x, i);
	}
}

int lca(int a, int b){
	if(dep[b] > dep[a]) return lca(b, a);

	for(int i=18; i>=0; --i)
		if(dep[jmp[i][a]] >= dep[b])
			a = jmp[i][a];

	if(a == b) return a;

	for(int i=18; i>=0; --i)
		if(jmp[i][a] != jmp[i][b])
			a = jmp[i][a], b = jmp[i][b];

	return jmp[0][a];
}

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int n, q; std::cin >> n >> q;
	for(int i=1; i<n; ++i){
		int a, b; std::cin >> a >> b;
		adj[--a].push_back(--b);
		adj[b].push_back(a);
	}

	dfs(0, 0);

	for(int i=1; i<19; ++i)
		for(int j=0; j<n; ++j)
			jmp[i][j] = jmp[i-1][jmp[i-1][j]];

	while(q--){
		int a, b; std::cin >> a >> b, --a, --b;
		std::cout << dep[a] + dep[b] - 2*dep[lca(a, b)] << '\n';
	}
}
