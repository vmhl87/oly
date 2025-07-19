#include <iostream>
#include <vector>
#include <string>

int main(){
	std::string s; std::cin >> s;

	std::vector<int> r;

	for(int i=0; i<s.length(); ++i)
		if(s[i] == '#') r.push_back(i);

	for(int i=0; i<r.size(); i+=2)
		std::cout << r[i]+1 << ',' << r[i+1]+1 << '\n';
}
