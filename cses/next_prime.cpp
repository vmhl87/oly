#include <iostream>

using ll = long long;

bool prime(ll i){
	if(i % 2 == 0) return i == 2;
	for(ll j = 3; j*j <= i; j += 2)
		if(i % j == 0) return 0;
	return 1;
}

void test(){
	ll n; std::cin >> n;
	if(n == 1){
		std::cout << 2 << '\n';
		return;
	}
	if(n % 2 == 0) --n;
	for(; !prime(n = n+2););
	std::cout << n << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
