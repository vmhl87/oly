#include <iostream>
#include <iomanip>
#include <vector>

std::vector<int> adj[100];
int deg[100], size[100];

double down[100], up[100];

void dfs1(int i, int p){
	++size[i];

	for(int x : adj[i]) if(x != p){
		dfs1(x, i);
		down[i] += (1 + down[x]) * ((double)1 / deg[x]);
		size[i] += size[x];
	}
}

void dfs2(int i, int p){
	for(int x : adj[i]) if(x != p)
		for(int y : adj[i]) if(x != y && y != p)
			up[x] += (1 + down[y]) * (
					((double)1 / deg[i]) *
					((double)1 / deg[y]));

	for(int x : adj[i]) if(x != p)
		up[x] += (up[i] + 1) * ((double)1 / deg[i]);

	for(int x : adj[i]) if(x != p) dfs2(x, i);
}

int main(){
	int n; std::cin >> n;
	for(int i=1; i<n; ++i){
		int a, b; std::cin >> a >> b;
		adj[--a].push_back(--b);
		adj[b].push_back(a);
		++deg[b], ++deg[a];
	}

	dfs1(0, 0);
	dfs2(0, 0);

	double res = 0;
	for(int i=0; i<n; ++i) res += down[i] + up[i];

	std::cout << std::setprecision(12) << 1 + res/n << '\n';
}
