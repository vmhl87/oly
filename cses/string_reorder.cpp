#include <iostream>
#include <string>

int main(){
	std::string s; std::cin >> s;

	int c[256] = {}, t = 0, l = -1;
	for(char x : s) ++c[x], ++t;

	if(t > 1) for(int i=0; i<256; ++i)
		if(c[i] > (t+1)/2) std::cout << -1 << '\n', exit(0);

	for(int i=0; i<t; ++i){
		int force = -1;

		for(int j=0; j<256; ++j)
			if(c[j] > (t-i)/2) force = j;

		if(force == -1) for(int j=0; j<256; ++j)
			if(c[j] && j != l) { force = j; break; }

		std::cout << char(force), --c[force], l = force;
	}

	std::cout << '\n';
}
