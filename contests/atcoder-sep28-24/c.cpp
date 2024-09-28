#include <algorithm>
#include <iostream>

int main(){
	int n; std::cin >> n;

	int a = -1e9;
	for(int i=0; i<n; ++i){
		int x; std::cin >> x;
		a = std::max(a, x);
	}

	int b = -1e9;
	for(int i=0; i<n; ++i){
		int x; std::cin >> x;
		b = std::max(b, x);
	}

	std::cout << a + b << '\n';
}
