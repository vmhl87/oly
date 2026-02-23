#include <iostream>
#include <vector>

using ll = long long;
const int N = 1e5 + 1;

ll a[N];

int p[20][N];

int main(){
	int n, q; std::cin >> n >> q;

	for(int i=0; i<n; ++i)
		std::cin >> a[i], a[i] = a[i]*n + n - i;  // must be unique?
	
	std::vector<ll> s;

	for(int i=n-1; i>=0; --i){
		while(s.size() && a[s.back()] < a[i]) s.pop_back();
		p[0][i] = s.size() ? s.back() : n;
		s.push_back(i);
	}

	p[0][n] = n;

	for(int i=1; i<20; ++i)
		for(int j=0; j<=n; ++j)
			p[i][j] = p[i-1][p[i-1][j]];

	while(q--){
		int l, r; std::cin >> l >> r, --l, --r;

		int res = 1;
		for(int i=19; i>=0; --i)
			if(p[i][l] <= r) res += (1<<i), l = p[i][l];
		std::cout << res << '\n';
	}
}
