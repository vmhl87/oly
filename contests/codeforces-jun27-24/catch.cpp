#include <iostream>

int main(){
	int n; std::cin >> n;

	while(n--){
		int x, y; std::cin >> x >> y;

		if(y < -1) std::cout << "NO";
		else std::cout << "YES";

		std::cout << '\n';
	}
}
