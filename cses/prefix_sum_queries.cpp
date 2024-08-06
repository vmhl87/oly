// Prefix Sum Queries  -  https://cses.fi/problemset/task/2166/
//
// If we operate on the prefix sum array, this problem reduces
// to range updates and range queries. Each point update translates
// into an addition on a range of the prefix sums starting at that
// point, going to the end, and range query is trivial.
//
// Implemented with sqrt bucket rather than lazy segtree.

#include <iostream>

using LL = long long;
const LL sz = 256, ct = 790, SMALL = -1LL<<62;

// raw values - must store for delta computation
int v[200001];
// prefixes, buckets {max, lazy add}
LL a[205000], b[800][2];

void push(int i){
	if(b[i][1]) for(int j=0; j<sz; ++j) a[j+i*sz] += b[i][1];
	b[i][1] = 0;
}

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int n, q; std::cin >> n >> q, ++n;

	// setup buckets
	for(int i=0; i<ct; ++i) b[i][0] = SMALL;
	for(int i=1; i<n; ++i){
		std::cin >> v[i], a[i] = a[i-1]+v[i];
		b[i/sz][0] = std::max(b[i/sz][0], a[i]);
	}

	while(q--){
		int t; std::cin >> t;

		// update
		if(t&1){
			int k, u; std::cin >> k >> u, u -= v[k], v[k] += u;

			push(k/sz);

			// reprocess end bucket
			for(int i=k; i/sz==k/sz; ++i) a[i] += u;
			b[k/sz][0] = SMALL;
			for(int i=0; i<sz; ++i) b[k/sz][0] = std::max(b[k/sz][0], a[i+sz*(k/sz)]);

			// and others
			for(int i=1+k/sz; i<ct; ++i) b[i][0] += u, b[i][1] += u;

		// range query
		}else{
			int l, r; std::cin >> l >> r, --l;

			push(l/sz), push(r/sz);
			LL max = SMALL;
			if(l/sz == r/sz) for(int i=l; i<=r; ++i) max = std::max(max, a[i]);
			else{
				for(int i=1+l/sz; i<r/sz; ++i) max = std::max(max, b[i][0]);
				for(int i=l; i/sz==l/sz; ++i) max = std::max(max, a[i]);
				for(int i=sz*(r/sz); i<=r; ++i) max = std::max(max, a[i]);
			}

			// asking for prefix sum inside [a,b]; this corresponds to maximum
			// global prefix sum ending between a,b minus the offset of a
			std::cout << max-a[l] << '\n';
		}
	}
}
