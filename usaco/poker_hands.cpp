#include <iostream>
#include <fstream>

using ll = long long;

int main(){
	std::ifstream in("poker.in");
	std::ofstream out("poker.out");

	int n; in >> n;

	ll res = 0, last = 0;

	for(int i=0; i<n; ++i){
		int x; in >> x;
		res += std::max(0ll, x-last);
		last = x;
	}

	out << res << '\n';
}
