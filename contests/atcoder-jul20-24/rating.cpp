#include <iostream>

int main(){
	int r; std::cin >> r;
	if(r < 100) std::cout << 100 - r;
	else if(r < 200) std::cout << 200 - r;
	else if(r < 300) std::cout << 300 - r;
	std::cout << '\n';
}
