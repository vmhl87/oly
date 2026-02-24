// Solves https://cses.fi/problemset/task/3163/ Range Interval Queries
// by binary searching over the nodes of a merge sort tree, yielding
// log^2 query performance. Aggressively constant optimized.

#include <iostream>

const int N = 2e5;

int _arena[N*19], *arena = _arena;
int *b[N*2], sz[N*2]; // segtree nodes {values, size}

int count(int i, int l, int r){
	// heuristically fallback to linear search
	if(sz[i] < 20){
		int res = 0;
		for(int j=0; j<sz[i]; ++j)
			if(b[i][j] >= l && b[i][j] <= r) ++res;
		return res;
	}

	int p1 = -1, p2 = -1;

	// bitwise binary search carries
	for(int s=1<<(std::__lg(sz[i])); s; s/=2){
		if(p1+s < sz[i] && b[i][p1+s] < l) p1 += s;
		if(p2+s < sz[i] && b[i][p2+s] <= r) p2 += s;
	}

	return p2-p1;
}

int main(){
	// what constant factor?
	std::cin.tie(0) -> sync_with_stdio(0);

	int n, q; std::cin >> n >> q;
	for(int i=0; i<n; ++i) std::cin >> arena[i];

	// build merge sort tree, allocate from arena for efficiency
	for(int i=0; i<n; ++i) b[i+n] = arena++, sz[i+n] = 1;

	for(int i=n-1; i; --i){
		sz[i] = sz[i*2] + sz[i*2+1];

		b[i] = arena, arena += sz[i];
		
		int p1 = 0, p2 = 0, p3 = 0;

		while(p1 < sz[i*2] && p2 < sz[i*2+1]){
			if(b[i*2][p1] < b[i*2+1][p2]) b[i][p3++] = b[i*2][p1++];
			else b[i][p3++] = b[i*2+1][p2++];
		}

		while(p1 < sz[i*2]) b[i][p3++] = b[i*2][p1++];
		while(p2 < sz[i*2+1]) b[i][p3++] = b[i*2+1][p2++];
	}

	while(q--){
		int w, x, y, z; std::cin >> w >> x >> y >> z, --w;

		int res = 0;

		// segtree range query -> binary search in node
		for(w+=n, x+=n; w<x; w/=2, x/=2){
			if(w&1) res += count(w++, y, z);
			if(x&1) res += count(--x, y, z);
		}

		std::cout << res << '\n';
	}
}
