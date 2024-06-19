// Increasing Subsequence 2  -  https://cses.fi/problemset/task/1748/
//
// We can formulate this question as DP:
// Given the following array:
//         ____A___B
// We can see that if B > A, all increasing subsequences ending at A
// will correspond to increasing subsequences passing through A and
// ending at B.
//
// Therefore, the number of increasing subsequences ending at an index
// I of the array will be the sum of all increasing subsequences ending
// at indices J such that a[I] > a[J], plus one - because the sequence
// containing only I is a valid increasing subsequence.
//
// We can implement this using some datastructure that allows us to
// efficiently query for all elements in some section of the array
// such that their values are less than some target.
//
// A segment tree works nicely for this. If we sort the values in the
// array prior to building the tree, then finding all indexes of value
// is equivalent to a range query upon the segtree. In order to enforce
// that subsequences only move left to right, we make the subsequence
// count of all elements in the segtree initially zero, and walk the
// array from left to right, computing subsequence counts and placing
// into the segtree as we go.

#include <algorithm>
#include <iostream>
#include <array>

int main(){
	int n; std::cin >> n;
	
	// because we need to process elements into the segtree at the
	// order they appear in the initial array, we must retain order
	// while also simultaneously sorting
	std::array<int, 2> a[n];
	for(int i=0; i<n; ++i) std::cin >> a[i][0], a[i][1] = i;

	std::sort(a, a+n);

	// reversal array
	int r[n]; for(int i=0; i<n; ++i) r[a[i][1]] = i;

	// segtree - first element stores the maximum value of a node
	// beneath it, and second element stores the number of subsequences
	// ending at any of its children nodes (and grandchildren, etc.)
	std::array<int, 2> seg[n<<1];
	for(int i=0; i<n<<1; ++i) seg[i][1] = 0;

	// maintain left to right order across the segment tree - fix the
	// wraparound portion or traversal will not work
	int leaf = 1 << std::__lg(n*2 - 1);
	for(int i=0; i<n; ++i) seg[n + (leaf-n+i)%n][0] = a[i][0];
	for(int i=n-1; i; --i)
		seg[i][0] = (seg[i<<1][0] > seg[i<<1|1][0] ? seg[i<<1][0] : seg[i<<1|1][0]);

	int res = 0;
	constexpr int M = 1e9 + 7;

	for(int i=0; i<n; ++i){
		// compute this entire section - starts at 1, for the identity
		int sect = 1;

		// walk the segtree from the root node, computing the total
		// subsequences that can chain into this node
		for(int p = 1;;){
			// mostly standard segtree traversal
			if(p < n){
				if(seg[p<<1][0] < a[r[i]][0])
					sect = (sect + seg[p<<1][1]) % M, p = p<<1|1;
				else p <<= 1;
			}else{
				if(seg[p][0] < a[r[i]][0]) sect = (sect + seg[p][1]) % M;
				break;
			}
		}

		// update segtree
		for(int p = n + (leaf-n+r[i])%n; p; p >>= 1) seg[p][1] = (seg[p][1] + sect) % M;

		// update result
		res = (res + sect) % M;
	}

	std::cout << res << '\n';
}
