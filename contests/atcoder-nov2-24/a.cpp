#include <algorithm>
#include <iostream>

int balls[4];

int main(){
	for(int i=0; i<4; ++i) std::cin >> balls[i];
	std::sort(balls, balls+4);

	std::cout << std::max((int)(balls[1] == balls[2]), ((int)(balls[0] == balls[1]) + (balls[2] == balls[3]))) << '\n';
}
