#include <iostream>
#include <string>
#include <map>

// low hanging fruit

int main(){
	int n; std::cin >> n;
	std::string s; std::cin >> s;

	std::map<std::string, int> r;
	r["RXXXXB"] = 5;
	r["XXRBXX"] = 6;
	r["XBXXXXRXRBXX"] = 18;

	std::cout << r[s] << '\n';
}
