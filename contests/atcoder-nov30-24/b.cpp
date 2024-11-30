#include <iostream>
#include <vector>

int main(){
	int n, m; std::cin >> n >> m;

	std::vector<int> v;

	for(int i=0; i<n; ++i){
		char c; std::cin >> c;
		if(c == '@') v.push_back(i);
	}

	while(m--) v.pop_back();

	for(int i=0, j=0; i<n; ++i){
		if(j < v.size() && v[j] == i){
			std::cout << '@';
			++j;
		}else std::cout << '.';
	}

	std::cout << '\n';
}
