// Dynamic Range Minimum Test  -  https://dmoj.ca/problem/segtree

#include <iostream>

int tree[200002];

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int n, m; std::cin >> n >> m;

	for(int i=0; i<n; ++i) std::cin >> tree[i+n];
	for(int i=n-1; i; --i) tree[i] = std::min(tree[i<<1], tree[i<<1|1]);

	while(m--){
		char t; std::cin >> t;

		if(t == 'Q'){
			int l, r, res = 1000000; std::cin >> l >> r, ++r;

			for(l += n, r += n; l < r; l >>= 1, r >>= 1){
				if(l&1) res = std::min(res, tree[l++]);
				if(r&1) res = std::min(res, tree[--r]);
			}

			std::cout << res << '\n';
		}else{
			int x, v; std::cin >> x >> v, tree[x+n] = v;
			for(x = (x+n)/2; x; x >>= 1) tree[x] = std::min(tree[x<<1], tree[x<<1|1]);
		}
	}
}
