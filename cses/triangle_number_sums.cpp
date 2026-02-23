#include <iostream>
#include <cmath>

using ll = long long;

void test(){
	ll n; std::cin >> n;

	int res = 0;

	for(int i=std::ceil(std::sqrt(n*2)); i>=1; --i){
		ll j = (i+1)*((ll)i) / 2;
		while(n >= j) ++res, n -= j;
	}

	std::cout << res << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
