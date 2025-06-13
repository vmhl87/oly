#include <iostream>
#include <set>

int main(){
	int n; std::cin >> n;
	std::set<int> s;
	for(int i=0, j; i<n; ++i)
		std::cin >> j, s.insert(j);
	std::cout << s.size() << '\n';
	for(int x : s) std::cout << x << ' ';
	std::cout << "\n";
}
