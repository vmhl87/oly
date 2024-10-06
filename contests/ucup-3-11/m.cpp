#include <algorithm>
#include <iostream>

using ll = long long;

int a[5000], b[5000], c[5000], l[5000], r[5000];

int main(){
	int n, m; std::cin >> n >> m;
	for(int i=0; i<n; ++i) std::cin >> a[i], l[i] = i-1, r[i] = i+1;
	for(int i=0; i<m; ++i) std::cin >> b[i];

	std::sort(a, a+n), std::sort(b, b+m);

	for(int i=0, p=0; i<m; ++i){
		while(r[p] < n &&
				std::abs(a[r[p]] - b[i]) <= std::abs(a[p] - b[i]))
			p = r[p];
		while(l[p] >= 0 &&
				std::abs(a[l[p]] - b[i]) <= std::abs(a[p] - b[i]))
			p = l[p];
		c[i] = a[p];
		//std::cout << "matching " << b[i] << " with " << a[p] << '\n';
		if(r[p] < n) l[r[p]] = l[p];
		if(l[p] >= 0) r[l[p]] = r[p];
		if(r[p] < n) p = r[p];
		else p = l[p];
	}

	std::sort(c, c+m);

	ll res = 0;
	for(int i=0; i<m; ++i) res += std::abs(b[i] - c[i]);
	std::cout << res << '\n';
}
