#include <iostream>

int main(){
	int t = 0;
	for(int i=0; i<6; ++i){
		for(int j=0; j<6; ++j){
			t += std::abs(i-j);
		}
	}
	std::cout << t << '\n';
}
