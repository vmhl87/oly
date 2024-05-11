// Josephus Problem 2  -  https://cses.fi/problemset/task/2163/
// I realized that this problem is essentially isomorphic to
// List Removals: we basically need to be able to locate and remove
// an arbitrary element of a list, and update the rest of it.
// I used a segment tree where each node stored the number
// of nondeleted nodes underneath it, and locating a node was as
// easy as traversing down from the root node and picking the
// correct branch.

#include <iostream>

int main(){
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int n, k; std::cin >> n >> k;
	// implicit segtree - no need for vector!
	int tree[n<<1];
	for(int i=0; i<n; ++i) tree[i+n] = 1;
	for(int i=n-1; i>0; --i)
		tree[i] = tree[i<<1] + tree[i<<1|1];
	// starts at position 0
	int at = 0, lb = 1 << std::__lg((n<<1) - 1);
	// s = ring size (# of children remaining)
	for(int s=n; s>0; --s){
		if(s < n) std::cout << ' ';
		// advance position, skip k children
		at = (at + k) % s;
		// p = current node, t = index in current tree of
		// target node (1-indexed)
		int p = 1, t = at + 1;
		while(p < n){
			// multiply p by two; it is now the node of the
			// left-branch tree
			p <<= 1;
			// if the target index is too big to exist inside
			// the left-branch tree, we need to look in the
			// right-branch tree. To do this, we increment p,
			// but we also need to reduce the target index
			// by the size of the left tree, as the zeroth index
			// of the right tree corresponds to 1 more than the
			// last index of the left tree.
			if(t > tree[p]) t -= tree[p++];
		}
		// p is now the correct leaf node, now find the child
		// associated with it (because of the implementation of
		// bottom-up segtree this needs the position of the wrap
		// around spot, here as `lb`
		std::cout << 1 + ((n + p - lb) % n);
		// update segtree
		for(; p; p >>= 1) --tree[p];
	}
	std::cout << '\n';
}
