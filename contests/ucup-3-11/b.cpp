#include <iostream>

using ll = long long;
const ll m = 998244353;

ll dp[3001][3000];

ll fact[3003];

ll pow(ll i, int p){
	ll res = 1;
	for(; p; i=i*i%m, p/=2)
		if(p&2) res = res*i % m;
	return res;
}

ll inv(int i){
	return pow(i, m-2);
}

ll nck(int n, int k){
	return fact[n] * inv(fact[k] * fact[n-k] % m) % m;
}

int main(){
	fact[0] = 1;
	for(int i=1; i<3003; ++i) fact[i] = i * fact[i-1] % m;

	int n, m; std::cin >> n >> m;
	for(int i=0; i<n; ++i) std::cin >> a[i];

	dp[0][0] = 1;
	for(int i=0; i<n; ++i)
		for(int c=n-1; c>=0; --c)
			for(int s=m-a[i]-1; s>=0; --s)
				dp[c+1][s+a[i]] += dp[c][s],
				dp[c+1][s+a[i]] %= m;

	ll res = 0;

	for(int c=0; c<=n; ++c){
		ll count = nck(n, c);
		for(int s=0; s<m; ++s)
			count += m - dp[c][s];
		count %= m;
	}

	std::cout << res << '\n';
}
