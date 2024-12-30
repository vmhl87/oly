#include <iostream>

using ll = long long;
const int N = 2e5;

ll a[N];

ll best(int l, int r, int k, ll p){
	if(!k) return p;

	ll res = 0;

	for(int i=l; i<r; ++i){
		if(r-l >= k)
			res = std::max(res, best(i+1, r, k-1, p^a[i]));
		else break;
	}

	return res;
}

int main(){
	ll t = 0;
	int n, k; std::cin >> n >> k;
	for(int i=0; i<n; ++i) std::cin >> a[i], t ^= a[i];

	ll res;

	if(k+k > n) res = best(0, n, n-k, t);
	else res = best(0, n, k, 0);

	std::cout << res << '\n';
}
