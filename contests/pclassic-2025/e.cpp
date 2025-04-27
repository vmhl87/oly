#include <iostream>
#include <cmath>

using ll = long long;

bool op(ll i){
	ll res = 0, b = 1, o = i;
	for(; i; i/=10){
		res += b * (i%10);
		if(i%10 != 0) b *= 10;
	}
	ll z = std::sqrt(res);
	return res == z*z;
}

int main(){
	ll x, res = 0; std::cin >> x;
	for(ll i=1; i*i<=x; ++i) res += op(i*i);
	std::cout << res << '\n';
}
