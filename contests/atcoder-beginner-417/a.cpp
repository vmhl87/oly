#include <iostream>

int main(){
	int n, a, b; std::cin >> n >> a >> b;

	for(int i=0; i<n; ++i){
		char c; std::cin >> c;
		if(i >= a && i < n-b) std::cout << c;
	}

	std::cout << '\n';
}
