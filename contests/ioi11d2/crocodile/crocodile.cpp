#include "crocodile.h"

#include <vector>
#include <array>
#include <queue>

using ll = long long;
const int maxn = 100000;

std::vector<std::array<int, 3>> adj[maxn];
std::array<ll, 2> dist[maxn][2];
int deg[maxn];

std::queue<int> proc;
bool inq[maxn];

void enq(int i) { if(!inq[i] && deg[i] > 1) proc.push(i), inq[i] = 1; }

void check(int x, int i, ll d){
	if(dist[x][0][1] == i){
		if(dist[x][0][0] != d) enq(x);
		dist[x][0][0] = d;
		if(dist[x][0][0] < dist[x][1][0])
			std::swap(dist[x][0], dist[x][1]);
	}else if(dist[x][1][1] == i){
		if(dist[x][1][0] != d) enq(x);
		dist[x][1][0] = d;
	}else{
		if(d < dist[x][0][0]){
			dist[x][0][0] = d;
			dist[x][0][1] = i;
			if(dist[x][0][0] < dist[x][1][0])
				std::swap(dist[x][0], dist[x][1]);
			enq(x);
		}
	}
}

void done(int i){
	for(auto &[x, d, v] : adj[i]){
		if(!v) v = 1, ++deg[x];
		check(x, i, dist[i][0][0]+d);
	}
}

int travel_plan(int n, int m, int r[][2], int l[], int k, int p[]){
	for(int i=0; i<m; ++i){
		adj[r[i][0]].push_back({r[i][1], l[i], 0});
		adj[r[i][1]].push_back({r[i][0], l[i], 0});
	}

	for(int i=0; i<n; ++i) for(int a=0; a<2; ++a)
		dist[i][a] = {1ll<<61, -1};

	for(int i=0; i<k; ++i){
		dist[p[i]][0] = {0, -1}, dist[p[i]][1] = {0, -1};
		done(p[i]);
	}

	while(proc.size()){
		int t = proc.front(); proc.pop();
		inq[t] = 0;
		done(t);
	}

	return dist[0][0][0];
}
