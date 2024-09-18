#include "friend.h"

#include <iostream>
#include <vector>

using ll = long long;

std::vector<int> adj[1000];
int* weight;

ll ifno[1000], ifyes[1000];

void dfs(int i, int p){
	for(int x : adj[i]) if(x != p){
		dfs(x, i);
	}

	ifyes[i] = weight[i];

	for(int x : adj[i]) if(x != p)
		ifyes[i] += ifno[x],
		ifno[i] += std::max( ifyes[x], ifno[x] );
}

int find0(int n, int conf[], int host[]){
	for(int i=1; i<n; ++i){
		adj[i].push_back(host[i]);
		adj[host[i]].push_back(i);
	}

	weight = conf, dfs(0, -1);
	
	return std::max(ifyes[0], ifno[0]);
}

bool edge[10][10];

int findsmall(int n, int conf[], int host[], int prot[]){
	for(int i=1; i<n; ++i){
		if(prot[i] == 0 || prot[i] == 2){
			edge[i][host[i]] = 1;
			edge[host[i]][i] = 1;
		}
		if(prot[i] == 1 || prot[i] == 2){
			for(int j=0; j<i; ++j) if(edge[host[i]][j]){
				edge[i][j] = 1;
				edge[j][i] = 1;
			}
		}
	}

	ll best = 0;

	for(ll i=1; i<1<<n; ++i){
		ll sum = 0;
		for(int j=0; j<n; ++j) if(i & (1<<j)) sum += conf[j];
		bool works = 1;
		for(int a=0; a<n; ++a)
			for(int b=a+1; b<n; ++b)
				if(edge[a][b] && (i & (1<<a)) && (i & (1<<b)))
					works = 0;
		if(works) best = std::max(best, sum);
	}

	return best;
}

int find1(int n, int conf[], int host[]){
	ll res = 0;
	for(int i=0; i<n; ++i) res += conf[i];
	return res;
}

int root[1000][2];

int origin(int i){
	if(root[i][0] < 0) return i;
	return root[i][0] = origin(root[i][0]);
}

void unite(int a, int b){
	a = origin(a), b = origin(b);
	if(root[a][0] < root[b][0]){
		root[a][1] = std::max(root[a][1], root[b][1]);
		root[a][0] += root[b][0];
		root[b][0] = a;
	}else{
		root[b][1] = std::max(root[b][1], root[a][1]);
		root[b][0] += root[a][0];
		root[a][0] = b;
	}
}

int find2(int n, int conf[], int host[]){
	for(int i=0; i<n; ++i) root[i][0] = -1, root[i][1] = conf[i];
	for(int i=1; i<n; ++i) unite(i, host[i]);

	ll res = 0;

	for(int i=0; i<n; ++i) if(root[i][0] < 0)
		res += root[i][1];
	
	return res;
}

int findSample(int n,int confidence[],int host[],int protocol[]){
	if(n <= 10) return findsmall(n, confidence, host, protocol);

	bool only0 = 1, only1 = 1, only2 = 1;
	for(int i=1; i<n; ++i){
		if(protocol[i] != 0) only0 = 0;
		if(protocol[i] != 1) only1 = 0;
		if(protocol[i] != 2) only2 = 0;
	}

	if(only0) return find0(n, confidence, host);
	if(only1) return find1(n, confidence, host);
	if(only2) return find2(n, confidence, host);
	return 0;
}
