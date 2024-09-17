#include <ext/rope>
#include <iostream>

int main(){
	int n; std::cin >> n;
	__gnu_cxx::rope<int> r;
	for(int i=0; i<n; ++i){
		int t; std::cin >> t;
		r.push_back(t);
	}
	for(int i=0; i<n; ++i){
		int p; std::cin >> p;
		std::cout << r[p-1] << ' ', r.erase(p-1, 1);
	}
	std::cout << '\n';
}
