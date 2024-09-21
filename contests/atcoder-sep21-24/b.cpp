#include <iostream>
#include <vector>

int main(){
	int m; std::cin >> m;
	std::vector<int> res;

	int pow[13] = {1}; for(int i=1; i<13; ++i) pow[i] = pow[i-1] * 3;

	for(int i=12; i>=0; --i) while(m >= pow[i]) res.push_back(i), m -= pow[i];

	std::cout << res.size() << '\n';
	for(int x : res) std::cout << x << ' ';
	std::cout << '\n';
}
