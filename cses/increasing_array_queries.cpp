// UNFINISHED

#include <iostream>

const int sz = 256;
int a[200000], b[800][3];

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int n, q; std::cin >> n >> q;
	for(int i=0; i<n; ++i) std::cin >> a[i];
	for(int i=0, last=0; i<n; ++i){
		if((i&sz) == 0) last = 0, b[i/sz][1] = a[i];
		if(a[i] < last) b[i/sz][0] += last-a[i];
		else last = a[i], b[i/sz][2] = a[i];
	}

	while(q--){
		int l, r; std::cin >> l >> r, --l, --r;

		int res = 0, p = 0;

		if(l/sz == r/sz) for(int i=l; i<=r; ++i)
			res += std::max(0, p-a[i]), p = std::max(p, a[i]);
		else{
			for(int i=l; i/sz==l/sz; ++i)
				res += std::max(0, p-a[i]), p = std::max(p, a[i]);
			for(int i=1+l/sz; i<r/sz; ++i)
				res += b[i][0] + sz*std::max(0, p-b[i][1]),
					p = b[i][2]-b[i][1] + std::max(p, b[i][1]);
			for(int i=sz*(r/sz); i<=r; ++i)
				res += std::max(0, p-a[i]), p = std::max(p, a[i]);
		}

		std::cout << res << '\n';
	}
}
