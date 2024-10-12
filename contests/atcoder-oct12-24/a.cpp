#include <iostream>
#include <string>

int main(){
	int n; std::cin >> n;
	std::string s; std::cin >> s;
	int res = 0;
	for(int i=0; i+2<n; ++i)
		if(s[i]=='#' && s[i+1]=='.' && s[i+2]=='#')
			++res;
	std::cout << res << '\n';
}
