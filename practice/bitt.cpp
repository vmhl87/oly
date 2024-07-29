// Binary Indexed Tree Test  -  https://dmoj.ca/problem/ds1

#include <iostream>

using LL = long long;

const int LIM = 100001;

LL inplace[200002], counts[200004];

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int n, m; std::cin >> n >> m;

	for(int i=0; i<n; ++i) std::cin >> inplace[i+n], ++counts[inplace[i+n]+LIM];
	for(int i=n-1; i; --i) inplace[i] = inplace[i<<1] + inplace[i<<1|1];
	for(int i=LIM-1; i; --i) counts[i] = counts[i<<1] + counts[i<<1|1];

	while(m--){
		char c; std::cin >> c;
		if(c == 'C'){
			int x, v; std::cin >> x >> v, --x;
			for(int p=inplace[x+n]+LIM; p; p >>= 1) --counts[p];
			for(int p=v+LIM; p; p >>= 1) ++counts[p];
			v -= inplace[x+n];
			for(x += n; x; x >>= 1) inplace[x] += v;

		}else if(c=='S'){
			int l, r; std::cin >> l >> r, --l;
			LL res = 0;
			for(l += n, r += n; l < r; l >>= 1, r >>= 1){
				if(l&1) res += inplace[l++];
				if(r&1) res += inplace[--r];
			}
			std::cout << res << '\n';

		}else{
			int v; std::cin >> v;
			int l = 0, r = v+1, res = 0;
			for(l += LIM, r += LIM; l < r; l >>= 1, r >>= 1){
				if(l&1) res += counts[l++];
				if(r&1) res += counts[--r];
			}
			std::cout << res << '\n';
		}
	}
}
