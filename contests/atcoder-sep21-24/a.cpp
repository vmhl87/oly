#include <iostream>
#include <string>

int main(){
	std::string s; std::cin >> s;
	for(char x : s) if(x != '.') std::cout << x;
	std::cout << '\n';
}
