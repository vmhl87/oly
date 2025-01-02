#include <algorithm>
#include <iostream>
#include <iomanip>

const int N = 1e5;

int a[N], idx[N], t[N*2], n;

int o(int i){
	int r = n-1;

	for(int s=1<<17; s; s/=2)
		if(r >= s && idx[r-s] >= -i)
			r -= s;

	return r;
}

int rng(int i){
	int res = 0;
	for(int l=n, r=i+n; l<r; l/=2, r/=2){
		if(l&1) res += t[l++];
		if(r&1) res += t[--r];
	}
	return res;
}

int main(){
	std::cout << std::fixed << std::setprecision(12);

	std::cin >> n;

	for(int i=0; i<n; ++i) std::cin >> a[i],
		idx[i] = -a[i];

	std::sort(idx, idx+n);

	long double res = 0;

	for(int i=0; i<n; ++i){
		int x = o(a[i]);
		res += 1 + rng(x);
		for(x+=n; x; x/=2) ++t[x];
	}

	std::cout << res/n << '\n';
}
