#include "game.h"

#include <iostream>

bool used[1500][1500];
bool vis[1500];
int n;

int root[1500];

int find(int i){
	if(root[i] < 0) return i;
	return root[i] = find(root[i]);
}

void merge(int a, int b){
	if(root[a] < root[b]) root[a] += root[b], root[b] = a;
	else root[b] += root[a], root[a] = b;
}

int left(int a, int b){
	int res = 0;
	for(int i=0; i<n; ++i)
		for(int j=i+1; j<n; ++j)
			if((find(i) == a && find(j) == b) ||
			   (find(i) == b && find(j) == a)) ++res;
	return res;
}

void initialize(int N) {
	n = N;
	for(int i=0; i<n; ++i) root[i] = -1;
}

bool dfs(int a, int b){
	if(a == b) return 1;
	if(!used[a][b]) return 1;
	vis[a] = 1;
	for(int i=0; i<n; ++i) if(!used[a][i] && a!=i && !vis[i])
		if(dfs(i, b)) return 1;
	return 0;
}

bool reachable(int a, int b){
	for(int i=0; i<n; ++i) vis[i] = 0;
	return dfs(a, b);
}

int hasEdge(int u, int v) {
	used[u][v] = 1, used[v][u] = 1;

	if(find(u) == find(v)) return 0;

	if(!reachable(u, v)){
		merge(find(u), find(v));
		return 1;
	}

	return 0;
}
