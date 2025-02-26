#include <iostream>

using ll = long long;
const int M = 1e9 + 7;

ll fact[(int)1e5 + 1];

ll inv(ll i){
	ll res = 1;
	for(int p=M-2; p; p/=2, i=i*i%M)
		if(p&1) res = res*i % M;
	return res;
}

ll nck(int n, int k){
	return fact[n] * inv(fact[k] * fact[n-k] % M) % M;
}

int main(){
	fact[0] = 1;
	for(int i=1; i<=1e5; ++i)
		fact[i] = fact[i-1]*i % M;

	int n, m; std::cin >> n >> m;

	ll res = 1;

	while(m--){
		int k; std::cin >> k;
		res = res * nck(k, n) % M;
	}

	std::cout << res << '\n';
}
