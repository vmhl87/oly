#include <iostream>
#include <string>

int main(){
	std::string s[12];
	for(int i=0; i<12; ++i) std::cin >> s[i];
	int res = 0;
	for(int i=0; i<12; ++i) if(i+1 == s[i].length()) ++res;
	std::cout << res << '\n';
}
