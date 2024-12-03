#include <iostream>

using ll = long long;
const int N = 1e5;

ll a[N][2];

int main(){
	freopen("cowjog.in", "r", stdin);
	freopen("cowjog.out", "w", stdout);

	int n, t; std::cin >> n >> t;

	for(int i=0; i<n; ++i)
		std::cin >> a[i][0] >> a[i][1];

	ll last = 2e18, res = 0;

	for(int i=n; i--;){
		ll cons = a[i][0] + a[i][1]*t;
		if(cons < last) last = cons, ++res;
	}
	
	std::cout << res << '\n';
}
