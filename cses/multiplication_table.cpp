#include <iostream>

using ll = long long;

int main(){
	ll n; std::cin >> n;

	ll left = 1 + (n*n)/2;

	for(ll i=1; i<=n*n; ++i)
		for(ll j=1; j*j<=i; ++j)
			if(i%j == 0 && i/j <= n)
				if((left -= 2-(j*j==i)) <= 0)
					std::cout << i << '\n', exit(0);
}
