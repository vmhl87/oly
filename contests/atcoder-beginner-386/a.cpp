#include <iostream>
#include <vector>
#include <map>
#include <set>

int main(){
	std::map<int, int> m;
	for(int i=0; i<4; ++i){
		int j; std::cin >> j;
		++m[j];
	}

	std::set<int> s;
	for(const auto &[a, b] : m)
		s.insert(b);

	std::vector<int> v;
	for(int i : s) v.push_back(i);
	v.push_back(0);

	std::cout << (((v[0] == 1 && v[1] == 3) || (v[0] == 2 && v[1] == 0)) ? "Yes\n" : "No\n");
}
