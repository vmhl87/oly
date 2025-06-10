#include <iostream>
#include <map>

using ll = long long;
const int m = 1e9 + 7;

std::map<int, int> count;

int main(){
	int n; std::cin >> n;
	for(int i=0, x; i<n; ++i) std::cin >> x, ++count[x];

	ll res = 1;

	for(const auto &[v, c] : count) res = res * (c+1) % m;

	std::cout << (res+m-1) % m << '\n';
}
