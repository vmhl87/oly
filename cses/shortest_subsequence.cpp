#include <iostream>
#include <string>
#include <bitset>

int main(){
	std::bitset<85> a;
	std::string s; std::cin >> s;

	for(char c : s){
		a[c] = 1;
		if(a.count() == 4)
			a.reset(), std::cout << c;
	}

	for(char c : "ACGT")
		if(!a[c]){
			std::cout << c << '\n';
			break;
		}
}
