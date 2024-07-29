// ICHB Selection Contest '17 Problem 3 - Parallel Universe

#include <iostream>

unsigned int tree[200000];

int main(){
	int n, q; std::cin >> n >> q;

	for(int i=0; i<n; ++i) std::cin >> tree[i+n];
	for(int i=n-1; i; --i) tree[i] = tree[i<<1] & tree[i<<1|1];

	while(q--){
		char t; std::cin >> t;

		if(t == 'U'){
			int i; std::cin >> i, std::cin >> tree[i+n-1];
			for(i = (i+n-1)/2; i; i >>= 1) tree[i] = tree[i<<1] & tree[i<<1|1];

		}else{
			unsigned int l, r, val; std::cin >> l >> r >> val, --l;
			for(l += n, r += n; l < r; l >>= 1, r >>= 1){
				if(l&1) val &= tree[l++];
				if(r&1) val &= tree[--r];
			}
			std::cout << val << '\n';
		}
	}
}
