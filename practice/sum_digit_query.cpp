// Range Update Point Query  -  https://codeforces.com/contest/1791/problem/F

#include <iostream>

int tree[400000], a[200000], n;

void test_case(){
	int q; std::cin >> n >> q;
	for(int i=0; i<n*2; ++i) tree[i] = 0;
	for(int i=0; i<n; ++i) std::cin >> a[i];
	
	while(q--){
		int t; std::cin >> t;

		if(t&1){
			int l, r; std::cin >> l >> r, --l;
			for(l += n, r += n; l < r; l /= 2, r /= 2){
				if(l & 1) ++tree[l++];
				if(r & 1) ++tree[--r];
			}
		}else{
			int op = 0, res, x; std::cin >> x, --x, res = a[x];
			for(x += n; x; x /= 2) op += tree[x];

			for(int i=0; i<op&&res>9; ++i){
				int next = 0;
				while(res) next += res%10, res /= 10;
				res = next;
			}

			std::cout << res << '\n';
		}
	}
}

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);
	int t; std::cin >> t;
	while(t--) test_case();
}
