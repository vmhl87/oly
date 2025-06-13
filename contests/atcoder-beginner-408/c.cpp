#include <algorithm>
#include <iostream>

const int M = 2e5, N = 1e6;

int l[M], r[M], c[N];

int main(){
	int n, m; std::cin >> n >> m;
	for(int i=0; i<m; ++i) std::cin >> l[i] >> r[i], --l[i], --r[i];

	std::sort(l, l+m);
	std::sort(r, r+m);

	for(int i=0, ct=0, lp=0, rp=0; i<n; ++i){
		while(lp<m && l[lp] == i) ++lp, ++ct;
		c[i] = ct;
		while(rp<m && r[rp] == i) ++rp, --ct;
	}

	int b = c[0];
	for(int i=1; i<n; ++i) b = std::min(b, c[i]);
	std::cout << b << '\n';
}
