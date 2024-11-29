#include <iostream>
#include <numeric>

using ll = long long;
const int N = 2e5;

ll a[N], b[N], t[N*2];
int n;

ll range(int l, int r){
	ll res = t[n+l];
	for(l += n, r += n; l < r; l /= 2, r /= 2){
		if(l&1) res = std::gcd(res, t[l++]);
		if(r&1) res = std::gcd(res, t[--r]);
	}
	return res;
}

void test(){
	std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> a[i];
	for(int i=1; i<n; ++i) b[i-1] = std::abs(a[i]-a[i-1]);

	for(int i=0; i<n; ++i) t[i+n] = b[i];
	for(int i=n-1; i; --i) t[i] = std::gcd(t[i*2], t[i*2+1]);
	
	int best = 0;

	int l = 0, r = 0;

	for(; r<n; ++r){
		while(l<r && range(l, r) == 1) ++l;
		best = std::max(best, r-l);
	}

	std::cout << best+1 << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
