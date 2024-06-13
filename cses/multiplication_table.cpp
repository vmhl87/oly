#include <iostream>

int main(){
	int n; std::cin >> n;

	// diag = n numbers
	// pick the (n+1)/2 element
	// its shift is determined by
	//     ((n+1)/2 - 1)/2
	// and then compute
	
	int shift = ((n+1)/2 - 1)/2;

	std::cout << (long long)(n-shift)*(long long)(shift+1) << '\n';
}
