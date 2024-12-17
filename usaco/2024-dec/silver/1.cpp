#include <iostream>

using ll = long long;
const int N = 1e6;

int a[N];

void test(){
	int n; std::cin >> n;

	ll as = 0;

	for(int i=0; i<n; ++i)
		std::cin >> a[i],
		as += a[i];

	// # that elsie can get
	int k = (n-1)/2;

	ll s = 0;
	for(int i=0; i<k; ++i) s += a[i];

	ll res = s;

	for(int i=k-1; i>=0; --i){
		s += a[n-k+i] - a[i];
		res = std::max(res, s);
	}

	std::cout << as-res << ' ' << res << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
