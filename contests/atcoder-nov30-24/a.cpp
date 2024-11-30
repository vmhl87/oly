#include <iostream>

int main(){
	int n, m; std::cin >> n >> m;

	for(int i=0; i<n; ++i){
		char c; std::cin >> c;
		if(c == '.') ++m;
	}

	std::cout << m << '\n';
}
