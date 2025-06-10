#include <iostream>
#include <vector>

const int maxn = 2e5;

std::vector<int> adj[maxn];
int jmp[maxn], head[maxn], hld[maxn], dep[maxn];

int dfs(int i, int p){
	hld[i] = -1;
	int sz = 1, best = 0;
	for(int x : adj[i]) if(x != p){
		jmp[x] = i, dep[x] = dep[i]+1;
		int part = dfs(x, i);
		if(part > best) hld[i] = x, best = part;
		sz += part;
	}
	if(best*2 < sz) hld[i] = -1;
	return sz;
}

void dfs2(int i, int p, int h){
	head[i] = h;

	if(hld[i] != -1) dfs2(hld[i], i, h);

	for(int x : adj[i]) if(x != p && x != hld[i])
		dfs2(x, i, x);
}

int lca(int a, int b){
	while(head[a] != head[b]){
		if(dep[head[b]] > dep[head[a]]) std::swap(a, b);
		a = jmp[head[a]];
	}
	if(dep[b] > dep[a]) return a;
	return b;
}

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int n, q; std::cin >> n >> q;
	for(int i=1; i<n; ++i){
		int a, b; std::cin >> a >> b;
		adj[--a].push_back(--b);
		adj[b].push_back(a);
	}

	dfs(0, 0), dfs2(0, 0, 0);

	while(q--){
		int a, b; std::cin >> a >> b, --a, --b;
		std::cout << dep[a] + dep[b] - 2*dep[lca(a, b)] << '\n';
	}
}
