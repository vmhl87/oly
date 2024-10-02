#include <iostream>

using ll = long long;
const ll m = 1e9+7;

ll fact[220000];

ll inv(ll i){
	ll res = 1;
	for(ll p=m-2; p; p/=2){
		if(p&1) res = res*i % m;
		i = i*i % m;
	}
	return res;
}

ll nck(ll n, ll k){
	return fact[n] * inv(fact[k] * fact[n-k] % m) % m;
}

ll move(int x1, int y1, int x2, int y2){
	return nck(x2-x1+y2-y1, y2-y1);
}

int main(){
	fact[0] = 1;
	for(int i=1; i<220000; ++i){
		fact[i] = fact[i-1] * i % m;
	}

	int h, w; std::cin >> h >> w;
	int a, b; std::cin >> a >> b;

	ll res = 0;

	// all pos on divider
	for(int i=b; i<w; ++i){
		res += move(0, 0, h-1-a, i) * move(h-a, i, h-1, w-1) % m;
		res %= m;
	}

	std::cout << res << '\n';
}
