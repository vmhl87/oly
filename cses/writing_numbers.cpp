#include <iostream>

using ll = long long;

ll n;

ll sector(int d, ll x, ll p, ll sz){
	ll res = x/10; if(d==0) --res;
	if(d < x%10) ++res;

	res *= sz;

	if(d == x%10) res += p;

	return res;
}

ll dig(int d, ll x){
	ll res = 0, part = 1, sz = 1;

	while(x){
		res += sector(d, x, part, sz);
		part += (x%10)*sz;
		x /= 10, sz *= 10;
	}

	return res;
}

bool works(ll x){
	for(int i=0; i<10; ++i)
		if(dig(i, x) > n) return 0;
	return 1;
}

int main(){
	std::cin >> n;

	ll res = 1;

	for(ll i=1ll<<60; i; i/=2)
		if(works(i+res)) res += i;

	std::cout << res << '\n';
}
