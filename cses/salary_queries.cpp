#include <iostream>
#include <array>
#include <map>

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);
	int n, q; std::cin >> n >> q;
	std::map<int, int> all;
	int sal[n];
	for(int i=0; i<n; ++i){
		std::cin >> sal[i];
		++all[sal[i]];
	}
	std::array<int, 3> query[q];
	for(int i=0; i<q; ++i){
		char c; std::cin >> c >> query[i][1] >> query[i][2];
		query[i][0] = c;
		if(c == '!' && !all.count(query[i][2]))
			all[query[i][2]] = 0;
	}
	int s = all.size(), tree[s<<1], c = 0;
	for(auto &a : all){
		tree[s+c] = a.second;
		a.second = c++;
	}
	for(int i=s-1; i>0; --i) tree[i] = tree[i<<1] + tree[i<<1|1];
	for(const auto &a : query){
		if(a[0] == '!'){
			int v = s+all[sal[a[1]-1]];
			while(v) --tree[v], v >>= 1;
			v = s+all[a[2]];
			while(v) ++tree[v], v >>= 1;
			sal[a[1]-1] = a[2];
		}else{
			auto x = all.lower_bound(a[1]),
				 y = all.lower_bound(a[2]+1);
			int l, r;
			if(x == all.end()) l = s;
			else l = x->second;
			if(y == all.end()) r = s;
			else r = y->second;
			l += s, r += s;
			int ret = 0;
			while(l < r){
				if(l&1) ret += tree[l++];
				if(r&1) ret += tree[--r];
				l >>= 1, r >>= 1;
			}
			std::cout << ret << '\n';
		}
	}
}
