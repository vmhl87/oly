#include <iostream>
#include <set>

int main(){
	int n, m; std::cin >> n >> m;

	std::set<int> seen;

	while(m--){
		int f; char c; std::cin >> f >> c;
		if(c == 'F' || seen.count(f))
			std::cout << "No\n";
		else std::cout << "Yes\n", seen.insert(f);
	}
}
