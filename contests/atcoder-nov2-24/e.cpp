#include <iostream>

using ll = long long;

ll tree[400000], count[400000], n, m, offset;

void shift(int x) { offset = (offset+x) % m; }

void upd(int y){
	for(int x = y+m; x; x/=2)
		tree[x] += m-y, ++count[x];
}

void add() { upd(offset); }

ll range_sum(int l, int r){
	ll res = 0;
	for(l += m, r += m; l<r; l/=2, r/=2){
		if(l&1) res += tree[l++];
		if(r&1) res += tree[--r];
	}
	return res;
}

ll range_count(int l, int r){
	ll res = 0;
	for(l += m, r += m; l<r; l/=2, r/=2){
		if(l&1) res += count[l++];
		if(r&1) res += count[--r];
	}
	return res;
}

ll sum(){
	return range_sum(offset+1, m) + offset*range_count(offset+1, m) +
		range_sum(0, offset+1) - (m-offset)*range_count(0, offset+1);
}

int main(){
	std::cin >> n >> m;
	ll res = 0;

	for(int i=0; i<n; ++i){
		ll a; std::cin >> a;
		add(), shift(a);
		res += sum();
	}

	std::cout << res << '\n';
}
