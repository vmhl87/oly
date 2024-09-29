#include "race.h"

#include <iostream>
#include <vector>
#include <array>

using ll = long long;

std::vector<std::array<int, 2>> adj[200000];

int depth[1000];
ll dist[1000];

void dfs(int i, int p){
	for(const auto &[x, d] : adj[i]) if(x != p)
		depth[x] = depth[i]+1, dist[x] = dist[i]+d,
			dfs(x, i);
}

bool possible[200000][110];
int subpath[200000][110];

void dfs2(int i, int p){
	for(const auto &[x, d] : adj[i]) if(x != p){
		dfs2(x, i);

		for(int j=0; j+d<110; ++j) if(possible[x][j])
			possible[i][j+d] = 1,
				subpath[i][j+d] = std::min(subpath[i][j+d],
						subpath[x][j] + 1);
	}
}

int best_path(int n, int k, int h[][2], int l[]){
	for(int i=0; i<n-1; ++i){
		adj[h[i][0]].push_back({h[i][1], l[i]});
		adj[h[i][1]].push_back({h[i][0], l[i]});
	}

	int best = n;

	if(k <= 100){
		for(int i=0; i<n; ++i){
			possible[i][0] = 1;
			for(int j=1; j<110; ++j)
				subpath[i][j] = n;
		}

		dfs2(0, -1);

		/*
		for(int i=0; i<n; ++i)
			for(int j=0; j<=k; ++j)
				std::cout << subpath[i][j]%n << " \n"[j==k];
		*/

		for(int i=0; i<n; ++i)
			for(int j=0; j+j<=k; ++j)
				if(possible[i][j] && possible[i][k-j])
					best = std::min(best,
							subpath[i][j] + subpath[i][k-j]);
	}else{
		for(int i=0; i<n; ++i){
			dist[i] = 0, depth[i] = 0;
			dfs(i, -1);

			for(int j=0; j<n; ++j) if(dist[j] == k)
				best = std::min(best, depth[j]);
		}
	}

	return best == n ? -1 : best;
}
