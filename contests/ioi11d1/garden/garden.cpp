#include "garden.h"
#include "gardenlib.h"

#include <vector>

std::vector<int> adj[5000];

int find(int i, int k){
	int last = -1;

	while(k--){
		if(adj[i].size() == 1)
			last = i, i = adj[i][0];
		else if(adj[i][0] == last)
			last = i, i = adj[i][1];
		else last = i, i = adj[i][0];
	}

	return i;
}

void count_routes(int n, int m, int p, int r[][2], int q, int g[]){
	for(int i=0; i<m; ++i){
		adj[r[i][0]].push_back(r[i][1]);
		adj[r[i][1]].push_back(r[i][0]);
	}

	for(int x=0; x<q; ++x){
		int res = 0;

		for(int i=0; i<n; ++i)
			res += (find(i, g[x]) == p);

		answer(res);
	}
}
