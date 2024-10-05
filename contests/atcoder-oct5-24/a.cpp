#include <iostream>
#include <string>

int main(){
	std::string s; std::cin >> s;
	int e = s.length()-1;
	if(s[e] == 'n' && s[e-1] == 'a' && s[e-2] == 's') std::cout << "Yes\n";
	else std::cout << "No\n";
}
