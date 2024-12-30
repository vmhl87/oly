#include <iostream>
#include <string>

int main(){
	std::string s; std::cin >> s;

	char last = 0;
	int r = 0, res = 0;

	for(char c : s){
		if(c == last) ++r;
		else{
			if(last == '0') res += (r+1)/2;
			else res += r;
			last = c;
			r = 1;
		}
	}

	if(last == '0') res += (r+1)/2;
	else res += r;

	std::cout << res << '\n';
}
