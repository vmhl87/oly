#include <algorithm>
#include <iostream>
#include <array>

using ll = long long;
const int M = 2e5;

std::array<ll, 2> a[M];

int main(){
	ll n; int m; std::cin >> n >> m;

	for(int i=0; i<m; ++i) std::cin >> a[i][0] >> a[i][1];

	std::sort(a, a+m, [] (std::array<ll, 2> x, std::array<ll, 2> y) {
		return (x[0]-x[1]) < (y[0]-y[1]);
	});

	int p = 0;
	ll ct = 0;

	while(p < m){
		if(n >= a[p][0]){
			ll rem = 1+(n-a[p][0])/(a[p][0]-a[p][1]);
			n -= (a[p][0]-a[p][1])*rem, ct += rem;

		}else ++p;
	}

	std::cout << ct << '\n';
}
