#include <iostream>
#include <string>

int main(){
	std::string s; std::cin >> s;

	int run = 0;

	for(char c : s)
		if(c == '|'){
			if(run) std::cout << run << ' ';
			run = 0;
		}else ++run;

	std::cout << '\n';
}
