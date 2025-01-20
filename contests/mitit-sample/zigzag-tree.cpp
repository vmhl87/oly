#include <iostream>
#include <vector>

using ll = long long;
const int m = 998244353, N = 3e3;

std::vector<int> adj[N];
bool up[N];
int n;

void dfs1(int i, int p){
	for(int x : adj[i]) if(x != p)
		up[x] = up[i]^1, dfs1(x, i);
}

ll swap = 1;
int sz[N];

ll fact[N];

ll inv(ll a){
	int p = m-2;
	ll res = 1;
	for(; p; p/=2, a = a*a % m)
		if(p&1) res = res*a % m;
	return res;
}

ll nck(int n, int k){
	return fact[n] * inv(fact[k] * fact[n-k] % m) % m;
}

void dfs2(int i, int p){
	sz[i] = 1;

	for(int x : adj[i]) if(x != p)
		dfs2(x, i), sz[i] += sz[x];

	int r = sz[i] - 1;

	for(int x : adj[i]) if(x != p)
		swap = swap * nck(r, sz[x]) % m,
			 r -= sz[x];
}

int main(){
	fact[0] = 1;
	for(int i=0; i<N; ++i)
		fact[i+1] = fact[i] * (i+1) % m;

	std::cin >> n;

	for(int i=1; i<n; ++i){
		int a, b; std::cin >> a >> b;
		adj[--a].push_back(--b);
		adj[b].push_back(a);
	}

	dfs1(0, -1);

	dfs2(0, -1);
}
