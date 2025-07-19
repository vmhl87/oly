#include <iostream>
#include <set>

int main(){
	int n; std::cin >> n;

	std::set<int> x;

	for(int i=0; i<n; ++i){
		int r; std::cin >> r;
		x.insert(r);
	}

	int y; std::cin >> y;

	std::cout << (x.count(y) ? "Yes" : "No") << '\n';
}
