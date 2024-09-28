#include <iostream>

int main(){
	int pos[26];
	for(int i=0; i<26; ++i){
		char c; std::cin >> c;
		pos[c-'A'] = i;
	}
	
	int res = 0;
	for(int i=1; i<26; ++i)
		res += std::abs(pos[i] - pos[i-1]);

	std::cout << res << '\n';
}
