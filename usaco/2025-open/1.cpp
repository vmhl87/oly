#include <iostream>
#include <string>

using ll = long long;
const int m = 1e9 + 7;

std::string s;

ll fact[(int)1e6+1];

ll pow(ll a, ll p){
	ll res = 1;
	for(; p; p/=2, a=a*a%m)
		if(p&1) res = res*a%m;
	return res;
}

ll inv(ll a){
	return pow(a, m-2);
}

ll nck(ll n, ll k){
	return fact[n]*inv(fact[k]*fact[n-k] % m) % m;
}

int main(){
	int k, n; ll l; std::cin >> k >> n >> l;
	std::cin >> s;

	fact[0] = 1;
	for(int i=1; i<=n; ++i)
		fact[i] = fact[i-1]*i % m;

	ll res = 1, tail = 0;

	//for(ll i=0; i<l; ++i){
		for(int j=n-1; j>=0; --j){
			if(s[j] == 'O') ++tail;
			else{
				res = res*nck(tail, k) % m;
				tail -= k;
			}
		}
	//}

	std::cout << pow(res, l) << '\n';
}
