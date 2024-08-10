#include <iostream>
#include <string>

std::string s[100];

int main(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> s[i];
	int maxlen = 0;
	for(int i=0; i<n; ++i) maxlen = std::max(maxlen, (int)s[i].length());
	for(int x=0; x<maxlen; ++x){
		std::string buffer;
		for(int i=n-1; i>=0; --i){
			if(x <= s[i].length()-1) std::cout << buffer << s[i][x], buffer = "";
			else buffer += '*';
		}
		std::cout << '\n';
	}
}
