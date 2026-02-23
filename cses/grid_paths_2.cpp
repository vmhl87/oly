#include <algorithm>
#include <iostream>
#include <array>

using ll = long long;
const int N = 1e6, M = 1e3 + 2, m = 1e9 + 7;

ll fact[N*2+1], ifact[N*2+1];

ll inv(ll i){
	ll res = 1;
	for(ll p=m-2; p; p/=2, i=i*i % m)
		if(p&1) res = res*i % m;
	return res;
}

ll nck(int n, int k){
	return fact[n] * (ifact[k] * ifact[n-k] % m) % m;
}

std::array<int, 2> a[M];
ll res[M];

ll v(std::array<int, 2> x, std::array<int, 2> y){
	return nck(y[0]+y[1]-x[0]-x[1], y[0]-x[0]);
}

int main(){
	int n, q; std::cin >> n >> q;

	fact[0] = 1, ifact[0] = 1;
	for(int i=1; i<=n*2; ++i) fact[i] = fact[i-1]*i % m, ifact[i] = inv(fact[i]);

	for(int i=0; i<q; ++i) std::cin >> a[i][0] >> a[i][1];
	a[q++] = {n, n};

	std::sort(a, a+q, [](std::array<int, 2> x, std::array<int, 2> y){ return x[0]+x[1] < y[0]+y[1]; });

	for(int i=0; i<q; ++i){
		res[i] = v({1, 1}, a[i]);

		for(int j=0; j<i; ++j) if(a[j][0] <= a[i][0] && a[j][1] <= a[i][1])
			res[i] = (res[i]-v(a[j], a[i])*res[j]) % m;

		if(res[i] < 0) res[i] += m;
	}

	std::cout << res[q-1] << '\n';
}
