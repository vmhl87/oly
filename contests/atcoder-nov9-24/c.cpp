#include <algorithm>
#include <iostream>
#include <array>

using ll = long long;

std::array<ll, 2> x[200000];

int main(){
	ll n, m; std::cin >> n >> m;

	for(int i=0; i<m; ++i) std::cin >> x[i][0];
	for(int i=0; i<m; ++i) std::cin >> x[i][1];

	std::sort(x, x+m);

	ll res = 0, b = n;

	while(m--){
		ll l = std::min(x[m][1], b-x[m][0]+1);

		res += (b-x[m][0])*l - (l*(l-1))/2;

		b -= l;
	}

	if(b != 0) std::cout << -1;
	else std::cout << res;
	std::cout << '\n';
}
