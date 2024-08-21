#include <algorithm>
#include <iostream>

using ll = long long;

int a[200000];

int main(){
	int n; std::cin >> n;
	ll res = 0;
	for(int i=0; i<n; ++i){
		std::cin >> a[i];
		int d; std::cin >> d; res += d;
	}
	std::sort(a, a+n);
	ll comb = 0;
	for(int i=0; i<n; ++i){
		comb += a[i];
		res -= comb;
	}
	std::cout << res << '\n';
}
