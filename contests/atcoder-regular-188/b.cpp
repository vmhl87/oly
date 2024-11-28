#include <iostream>
#include <numeric>

void test(){
	int n, k; std::cin >> n >> k;
	std::cout << (
			std::gcd(n, k*2) == 1 ||
			(std::gcd(n, k*2) == 2 && (n/2)&1)
		? "Yes" : "No") << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
