#include <iostream>

int main(){
	int n; std::cin >> n;
	int diff = 0;
	char first; std::cin >> first;
	for(int i=1; i<n; ++i){
		char now; std::cin >> now;
		if(now != first) ++diff;
		first = now;
	}
	std::cout << (diff+1)/2 << '\n';
}
