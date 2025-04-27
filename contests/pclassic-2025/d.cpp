#include <iostream>

int main(){
	int x; std::cin >> x;

	char y; std::cin >> y;
	int now = y-'0';
	char lastop;

	for(int i=1; i<x; ++i){
		if(i&1){
			char op; std::cin >> op;
			lastop = op;
		}else{
			char y; std::cin >> y;
			int z = y-'0';

			if(lastop == '-') now -= z;
			if(lastop == '+') now += z;
			if(lastop == '*') now *= z;
			if(lastop == '$') now = now*z-now-z;
		}
	}

	std::cout << now << '\n';
}
