#include <iostream>
#include <set>

int main(){
	int n, m; std::cin >> n >> m;

	std::multiset<int> s;

	for(int i=0; i<n; ++i){
		int x; std::cin >> x;
		s.insert(x);
	}

	for(int i=0; i<m; ++i){
		int x; std::cin >> x;
		if(s.count(x)) s.erase(s.find(x));
	}

	for(int x : s) std::cout << x << ' ';
	std::cout << '\n';
}
