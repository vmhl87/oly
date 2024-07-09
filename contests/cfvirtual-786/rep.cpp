#include <iostream>
#include <string>

typedef long long LL;

void test_case(){
	std::string a, b; std::cin >> a >> b;

	for(char x : b) if(x == 'a'){
		if(b.length() > 1) std::cout << '-';
		std::cout << 1 << '\n';
		return;
	}

	LL res = 1;

	for(char x : a) if(x == 'a') res <<= 1;

	std::cout << res << '\n';
}

int main(){
	int t; std::cin >> t;

	while(t--) test_case();
}
