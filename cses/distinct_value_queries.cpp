#include <set>
#include <iostream>

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);
	int n, q; std::cin >> n >> q;
	std::set<int> tree[n<<1];
	for(int i=0; i<n; ++i){
		int t; std::cin >> t;
		int v = i+n;
		while(v && !tree[v].count(t)){
			tree[v].insert(t);
			v >>= 1;
		}
	}
	while(q--){
		int a, b; std::cin >> a >> b;
		std::set<int> ret;
		a += n-1, b += n;
		while(a < b){
			if(a&1){
				for(int i : tree[a]) ret.insert(i);
				++a;
			}
			if(b&1){
				--b;
				for(int i : tree[b]) ret.insert(i);
			}
			a >>= 1, b >>= 1;
		}
		std::cout << ret.size() << '\n';
	}
}
