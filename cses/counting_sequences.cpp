#include <iostream>

using ll = long long;
constexpr int m = 1e9 + 7;

ll pow(ll a, ll p){
	ll res = 1;
	for(; p; a=a*a%m, p/=2)
		if(p&1) res=res*a%m;
	return res;
}

ll inv(ll a){
	return pow(a, m-2);
}

ll fact[1000001];

ll nck(int n, int k){
	return fact[n] * inv(fact[k] * fact[n-k] % m) % m;
}

int main(){
	int n, k; std::cin >> n >> k;

	fact[0] = 1;
	for(int i=1; i<=k; ++i)
		fact[i] = fact[i-1]*i % m;

	ll res = 0;

	for(int i=k; i; --i){
		res += (((k-i) & 1 ? -1 : 1) * pow(i, n) % m) * nck(k, i) % m;
		res %= m; if(res < 0) res += m;
	}

	std::cout << res << '\n';
}
