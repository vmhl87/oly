#include <iostream>

int main(){
	int count[26] = {};
	for(int i=0; i<3; ++i){
		char c; std::cin >> c;
		count[c-'A']++;
	}

	std::cout << (count[0] == 1 && count[1] == 1 && count[2] == 1 ? "Yes" : "No") << '\n';
}
