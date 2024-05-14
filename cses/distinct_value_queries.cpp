#include <iostream>
#include <bitset>
#include <map>

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);
	int n, q; std::cin >> n >> q;
	std::bitset<200000> *tree = new std::bitset<200000>[n<<1];
	std::map<int, int> val;
	int c = 0;
	for(int i=0; i<n; ++i){
		int t; std::cin >> t;
		if(!val.count(t)) val[t] = c++;
		tree[i+n][val[t]] = 1;
	}
	for(int i=n-1; i; --i) tree[i] = tree[i<<1] | tree[i<<1|1];
	while(q--){
		int a, b; std::cin >> a >> b;
		std::bitset<200000> ret;
		a += n-1, b += n;
		while(a < b){
			if(a&1) ret |= tree[a++];
			if(b&1) ret |= tree[--b];
			a >>= 1, b >>= 1;
		}
		std::cout << ret.count() << '\n';
	}
}
