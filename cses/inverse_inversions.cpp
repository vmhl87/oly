#include <iostream>

using ll = long long;

int main(){
	ll n, m; std::cin >> n >> m;
	int l = 0, r = n;

	for(ll s=n; s-1; --s)
		while(l+s <= r && s*(s-1) <= m*2){
			for(int i=s; i; --i)
				std::cout << l+i << ' ';
			l += s, m -= (s*(s-1))/2;
		}

	for(int i=l; i<r; ++i)
		std::cout << i+1 << ' ';

	std::cout << '\n';
}
