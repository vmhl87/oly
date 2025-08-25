#include <iostream>

int main(){
	int x, y; std::cin >> x >> y;
	std::cout << ((x+y+12-1) % 12 + 1) << '\n';
}
