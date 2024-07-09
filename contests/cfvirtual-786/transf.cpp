#include <iostream>

void test_case(){
	int x, y; std::cin >> x >> y;
	
	if(y % x != 0){
		std::cout << "0 0\n";
		return;
	}

	int diff = y/x;

	std::cout << 1 << ' ' << diff << '\n';
}

int main(){
	int t; std::cin >> t;

	while(t--) test_case();
}
