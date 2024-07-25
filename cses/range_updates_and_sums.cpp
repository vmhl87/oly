// Range Updates And Sums  -  https://cses.fi/problemset/task/1735

// Intended to be solved by lazy segtree. I'm lazily propagating the
// learning of such technique to a later date, so sqrt bucketing it is.

#include <iostream>

using LL = long long;
// 256 is close enough to sqrt(2e5) and is a nice power of 2
const LL sq = 256;

int n;
// array values, bucket sums, lazy {set, add} q
LL a[200260], bucket[800], set[800], add[800];

// very similar to how push() works in segtree, but no recursive,
// as there is only one level of tree :D
void push(int i){
	if(set[i]){
		for(int j=0; j<sq; ++j) a[(i*sq)+j] = set[i];
		set[i] = 0;
	}
	if(add[i]){
		for(int j=0; j<sq; ++j) a[(i*sq)+j] += add[i];
		add[i] = 0;
	}
}

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int q; std::cin >> n >> q;

	// setup buckets. very simple!
	for(int i=0; i<n; ++i) std::cin >> a[i], bucket[i/sq] += a[i];

	while(q--){
		int t; std::cin >> t;

		// add query
		if(t == 1){
			int l, r, x; std::cin >> l >> r >> x, --l, --r;

			// because we'll be messing with individual array values on the
			// end segments, we need to push waiting updates
			push(l/sq), push(r/sq);

			// only on one bucket
			if(l/sq == r/sq) for(int i=l; i<=r; ++i) a[i] += x, bucket[l/sq] += x;
			// across multiple buckets
			else{
				// intermediate buckets - place lazy add update
				for(int i=1+l/sq; i<r/sq; ++i) add[i] += x, bucket[i] += (LL)x*sq;

				// left and right sides
				for(int i=l; i<sq*(1+l/sq); ++i) a[i] += x, bucket[l/sq] += x;
				for(int i=sq*(r/sq); i<=r; ++i) a[i] += x, bucket[r/sq] += x;
			}

		// set query - very similar
		}else if(t == 2){
			int l, r, x; std::cin >> l >> r >> x, --l, --r;

			push(l/sq), push(r/sq);

			if(l/sq == r/sq){
				bucket[l/sq] = 0;
				for(int i=l; i<=r; ++i) a[i] = x;
				for(int i=0; i<sq; ++i) bucket[l/sq] += a[i+sq*(l/sq)];

			}else{
				for(int i=1+l/sq; i<r/sq; ++i) set[i] = x, add[i] = 0, bucket[i] = (LL)x*sq;
				
				// recalculate buckets; no easier/better solution
				for(int i=l; i<sq*(1+l/sq); ++i) a[i] = x;
				bucket[l/sq] = 0;
				for(int i=0; i<sq; ++i) bucket[l/sq] += a[i+sq*(l/sq)];

				for(int i=sq*(r/sq); i<=r; ++i) a[i] = x;
				bucket[r/sq] = 0;
				for(int i=0; i<sq; ++i) bucket[r/sq] += a[i+sq*(r/sq)];
			}

		// range query
		}else{
			int l, r; std::cin >> l >> r, --l, --r;

			push(l/sq), push(r/sq);

			// literally the same as update query but we don't modify
			// values and instead accumulate a running sum
			LL sum = 0;

			if(l/sq == r/sq) for(int i=l; i<=r; ++i) sum += a[i];
			else{
				for(int i=1+l/sq; i<r/sq; ++i) sum += bucket[i];
				for(int i=l; i<sq*(1+l/sq); ++i) sum += a[i];
				for(int i=sq*(r/sq); i<=r; ++i) sum += a[i];
			}

			std::cout << sum << '\n';
		}
	}
}
