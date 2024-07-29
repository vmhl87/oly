#include <iostream>
#include <cmath>

int main(){
	int t; std::cin >> t;

	while(t--){
		int a, b, c; std::cin >> a >> b >> c;

		int d = a + b + c - std::min(a, std::min(b, c)) - std::max(a, std::max(b, c));

		std::cout << std::abs(a - d) + std::abs(b - d) + std::abs(c - d) << '\n';
	}
}
