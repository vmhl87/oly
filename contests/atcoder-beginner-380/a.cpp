#include <iostream>

int ct[256];

int main(){
	for(int i=0; i<6; ++i){
		char c; std::cin >> c;
		++ct[c];
	}

	std::cout << (ct['1'] == 1 && ct['2'] == 2 && ct['3'] == 3 ? "Yes" : "No") << '\n';
}
