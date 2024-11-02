#include <iostream>
#include <vector>
#include <set>
#include <map>

std::set<int> adj[100000];
int deg[100000], c;
std::vector<int> cycle[100000];
std::map<int, int> pos[100000];
bool use[100000];

void decycle(int i){
	int j = *(adj[i].begin()), l = i;
	while(j != i){
		pos[j][c] = cycle[c].size();
		cycle[c].push_back(j);
		--deg[l], --deg[j];
		adj[l].erase(j);
		adj[j].erase(l);
		l = j, j = *(adj[j].begin());
	}
	pos[i][c] = cycle[c].size();
	cycle[c++].push_back(i);
	--deg[l], --deg[i];
	adj[l].erase(i);
	adj[i].erase(l);
}

void print(int i, int j){
	use[i] = 1;
	for(int k=0; k<cycle[i].size(); ++k){
		int x = cycle[i][(k+j)%cycle[i].size()];
		while(pos[x].size()){
			auto [l, d] = *(pos[x].begin());
			pos[x].erase(l);
			if(!use[l]) print(l, d);
		}
		std::cout << ' ' << x+1;
	}
}

int root[100000], comps;

int find(int i){
	if(root[i] < 0) return i;
	return root[i] = find(root[i]);
}

void merge(int a, int b){
	if((a = find(a)) == (b = find(b))) return;
	if(root[a] < root[b]) root[a] += root[b], root[b] = a;
	else root[b] += root[a], root[a] = b;
	++comps;
}

int main(){
	int n, m; std::cin >> n >> m;
	for(int i=0; i<n; ++i) root[i] = -1;
	while(m--){
		int a, b; std::cin >> a >> b;
		++deg[--a], ++deg[--b];
		adj[a].insert(b);
		adj[b].insert(a);
		merge(a, b);
	}

	int ct = 0;
	for(int i=0; i<n; ++i) if(deg[i]) ++ct;
	if(++comps != ct || !deg[0]) std::cout << "IMPOSSIBLE\n", exit(0);

	for(int i=0; i<n; ++i)
		if(deg[i] & 1) std::cout << "IMPOSSIBLE\n",
			exit(0);

	for(int i=0; i<n; ++i) while(deg[i])
		decycle(i);

	std::cout << 1, print(0, 0), std::cout << '\n';
}
