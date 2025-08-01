// URL: https://codeforces.com/contest/2125/problem/D

#include <algorithm>
#include <iostream>
#include <array>

using ll = long long;
const int M = 998244353, N = 2e5;

//\\//
	struct fract{
		ll num, den;

		ll f(){
			ll res = num, b = den;

			for(int p=M-2; p; p/=2, b=b*b%M)
				if(p&1) res = res*b % M;

			return res;
		}
	};

	fract add(fract a, fract b){
		return {
			(a.num*b.den + b.num*a.den) % M,
			a.den*b.den % M
		};
	}

	fract mul(fract a, fract b){
		return {
			a.num*b.num % M,
			a.den*b.den % M
		};
	}

int l[N], r[N], p[N], q[N];
std::array<int, 3> s[N];
fract dp[N+1];

int main(){
	int n, m; std::cin >> n >> m;
	
	for(int i=0; i<n; ++i)
		std::cin >> l[i] >> r[i] >> p[i] >> q[i];

	for(int i=1; i<=m; ++i) dp[i] = {0, 1};
	dp[0] = {1, 1};

	for(int i=0; i<n; ++i) s[i] = {r[i], l[i], i};
	std::sort(s, s+n);

	for(int I=0; I<n; ++I){
		const auto &[r, l, i] = s[I];
		dp[r] = add(dp[r], mul(dp[l-1], {p[i], q[i]-p[i]}));
	}

	for(int i=0; i<n; ++i)
		dp[m] = mul(dp[m], {q[i]-p[i], q[i]});

	std::cout << dp[m].f() << '\n';
}
