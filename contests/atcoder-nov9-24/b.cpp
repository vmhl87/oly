#include <iostream>

int main(){
	int n, k; std::cin >> n >> k;
	
	int run = 0, res = 0;
	for(int i=0; i<n; ++i){
		char c; std::cin >> c;
		if(c=='O') ++run;
		else{
			res += run/k;
			run = 0;
		}
	}

	res += run/k;

	std::cout << res << '\n';
}
