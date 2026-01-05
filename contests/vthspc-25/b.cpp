#include <algorithm>
#include <iostream>
#include <vector>

using ll = long long;
const int N = 5e5 + 10, M = 1e9 + 7;

std::vector<int> adj[N], bdj[N];

int a[N], in[N], tmr;
ll dp[N][2];

int lift[20][N], d[N];
ll fib[N];

void dfs3(int i, int p){
	dp[i][0] = 1, dp[i][1] = 1;

	for(int j : bdj[i]) if(j != p){
		dfs3(j, i);

		int dist = d[j]-d[i];

		dp[i][0] = dp[i][0]*
			((dp[j][0]*fib[dist+1]%M)+(dp[j][1]*fib[dist]%M)) % M;
		dp[i][1] = dp[i][1]*
			((dp[j][0]*fib[dist]%M)+(dp[j][1]*fib[dist-1]%M)) % M;
	}
}

ll fact[N*2], invfact[N*2];

ll inv(ll i){
	if(i == 1) return 1;
	
	ll res = 1;
	for(int p = M-2; p; p/=2, i = i*i % M)
		if(p&1) res = res*i % M;
	return res;
}

ll nck(int n, int k){
	if(k > n) return 0;
	return (fact[n] * (invfact[k]*invfact[n-k] % M)) % M;
}

void dfs(int i, int p){
	lift[0][i] = p, d[i] = d[p]+1, in[i] = ++tmr;

	for(int j : adj[i]) if(j != p) dfs(j, i);
}

int lca(int A, int B){
	int a = A, b = B;

	if(d[b] > d[a]) std::swap(a, b);

	for(int i=0; i<20; ++i) if((d[a]-d[b]) & (1<<i))
		a = lift[i][a];

	if(a == b) return a;

	for(int i=19; i>=0; --i) if(lift[i][a] != lift[i][b])
		a = lift[i][a], b = lift[i][b];

	return lift[0][a];
}

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int n, q; std::cin >> n >> q;

	fact[0] = 1, invfact[0] = 1;
	for(int i=1; i<=2*n; ++i) fact[i] = fact[i-1]*i % M, invfact[i] = inv(fact[i]);
	fib[0] = 0, fib[1] = 1;
	for(int i=2; i<=n+3; ++i) fib[i] = (fib[i-1]+fib[i-2]) % M;

	for(int i=1; i<n; ++i){
		int a, b; std::cin >> a >> b, --a, --b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	dfs(0, 0);

	for(int i=1; i<20; ++i)
		for(int j=0; j<n; ++j)
			lift[i][j] = lift[i-1][lift[i-1][j]];

	while(q--){
		int t; std::cin >> t;

		if(t == 1){
			int x, y, r; std::cin >> x >> y >> r;
			int l = lca(--x, --y), dist = d[x] + d[y] + 1 - d[l]*2;

			std::cout << nck(dist+1-r, r) << '\n';

		}else{
			int m; std::cin >> m;
			for(int i=0; i<m; ++i) std::cin >> a[i], --a[i];
			std::sort(a, a+m, [] (int x, int y) { return in[x] < in[y]; });

			int L = lca(a[0], a[1]);
			for(int i=2; i<m; ++i) L = lca(L, a[i]);

			std::vector<int> st = {0};
			bdj[0].clear();

			for(int i=0; i<m; ++i){
				int u = a[i];
				if(u == 0) continue;
				int l = lca(u, st.back());
				if(l != st.back()){
					while(st.size() >= 2 && in[l] < in[st[st.size()-2]]){
						bdj[st.back()].push_back(st[st.size()-2]);
						bdj[st[st.size()-2]].push_back(st.back());
						st.pop_back();
					}
					if(st.size() >= 2 && in[l] != in[st[st.size()-2]]){
						bdj[l].clear();
						bdj[st.back()].push_back(l);
						bdj[l].push_back(st.back());
						st.back() = l;
					}else{
						bdj[st.back()].push_back(l);
						bdj[l].push_back(st.back());
						st.pop_back();
					}
				}
				bdj[u].clear();
				st.push_back(u);
			}

			while(st.size() > 1){
				bdj[st.back()].push_back(st[st.size()-2]);
				bdj[st[st.size()-2]].push_back(st.back());
				st.pop_back();
			}

			dfs3(0, 0);

			std::cout << (dp[L][0]+dp[L][1])%M << '\n';
		}
	}
}
