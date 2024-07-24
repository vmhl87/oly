// 2019 December Gold P2 Milk Visits  -  https://usaco.org/index.php?page=viewproblem2&cpid=970

#include <iostream>
#include <fstream>
#include <vector>
#include <set>

const int MAXN = 100000;

// binlift structures
int at[MAXN], depth[MAXN], par[MAXN], jump[MAXN];
std::set<int> along[MAXN];

std::vector<int> adj[MAXN];

// single pass and accumulate not only jump structure locations,
// but also update sets (somehow this avoids tle?)
void dfs(int i, int p){
	for(int x : adj[i]) if(x != p){
		if(depth[i] + depth[jump[jump[i]]] == depth[jump[i]]*2){
			jump[x] = jump[jump[i]];
			for(int e : along[jump[i]]) along[x].insert(e);
			for(int e : along[i]) along[x].insert(e);
		}else jump[x] = i;
		along[x].insert(at[x]);

		depth[x] = depth[i]+1, par[x] = i, dfs(x, i);
	}
}

int main(){

// DEFINITELY weirdest I/O ive ever used, and that's saying something
#define fin std::cin
#ifndef fin
	std::ifstream fin("milkvisits.in");
	std::ofstream fout("milkvisits.out");
#else
#define fout std::cout
#endif

	int n, m; fin >> n >> m;
	for(int i=0; i<n; ++i) fin >> at[i], --at[i];

	for(int i=1; i<n; ++i)
		int a, b; fin >> a >> b, --a, --b,
			adj[a].push_back(b), adj[b].push_back(a);

	dfs(0, -1);

	while(m--){
		int a, b, c; fin >> a >> b >> c, --a, --b, --c;
		int out = 0;
		
		// binlift pass from a, b -> LCA and check all relevant
		// sets along the pass for type c

		if(depth[a] < depth[b]) std::swap(a, b);

		out |= (at[a] == c | at[b] == c);

		while(depth[a] > depth[b]){
			if(depth[jump[a]] < depth[b]) a = par[a];
			else out |= along[a].count(c), a = jump[a];
			out |= at[a] == c;
		}

		while(a != b){
			if(jump[a] == jump[b]) a = par[a], b = par[b];
			else out |= along[a].count(c), out |= along[b].count(c),
				a = jump[a], b = jump[b];
			out |= (at[a] == c | at[b] == c);
		}

		fout << out;
	}

	fout << '\n';
}
