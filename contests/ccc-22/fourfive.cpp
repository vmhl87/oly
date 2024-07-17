#include <iostream>

int main(){
	int n; std::cin >> n;

	int max4 = n/4;

	int min4 = 1 + (n-1)/5;

	std::cout << max4-min4+1 << '\n';
}
