#include <iostream>
#include <map>

int t[40];

int main(){
	int n, x; std::cin >> n >> x;
	for(int i=0; i<n; ++i) std::cin >> t[i];

	std::map<int, int> count;
	++count[0];

	for(int i=0; i<n; ++i){
		std::map<int, int> next;
		for(const auto &[j, c] : count)
			if(j+t[i] <= x) next[j+t[i]] += c;
		for(const auto &[j, c] : next)
			count[j] += c;
	}

	std::cout << count[x] << '\n';
}
