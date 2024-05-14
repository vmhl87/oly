/*  List Removals  -  https://cses.fi/problemset/task/1749/

	This problem seems difficult. We can, however, use
	a clever segment tree.
	
	We can build a segment tree that stores the number of
	non-removed elements under each node, and use this
	information to traverse down the tree until we get
	to the correct leaf. We then can print out its value,
	and set its "count" to 0, and then recursively update
	all of its ancestors to match.
	
	We must make an important modification to the segment
	tree in order for this to work - we need the leaves
	to be ordered not from lowest to highest, but rather
	in an order that does not wrap any elements around
	the boundary where there is such.
	
	This approach runs in O(n log n).
*/

#include <iostream>

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int n; std::cin >> n;

	// build segment tree - l = wraparound index
	int tree[n<<1], l = 1 << std::__lg((n<<1) + 1);
	// fill with size of subtree at each node
	for(int i=0; i<n; ++i) tree[i+n] = 1;
	for(int i=n-1; i>0; --i) tree[i] = tree[i<<1] + tree[i<<1|1];
	
	// input values of array
	int val[n];
	// we need to shift around because in this bottom up segtree
	// implementation, there is a wraparound portion that must be
	// accounted for when retrieving values in order
	for(int i=0; i<n; ++i) std::cin >> val[(l+i)%n];

	for(int i=0; i<n; ++i){
		if(i) std::cout << ' ';

		// input position, j = current node index (starts at root)
		int p, j = 1; std::cin >> p;
		// repeat until j is a leaf
		while(j < n){
			// instead of coming back to update segtree later, we
			// can just decrement the node right now before we
			// move down, since this node is guaranteed to be
			// in the final path, and we won't need it after this.
			--tree[j];
			// move down to the left subtree
			j <<= 1;
			// if the left subtree is too small to contain the pos
			// we are looking for, we clip the position to the right
			// subtree, and increment j to go to the right child
			if(tree[j] < p) p -= tree[j], ++j;
		}

		// print out and set this leaf to 0 (it isn't touched in
		// the while loop because it breaks before that point)
		std::cout << val[j-n], tree[j] = 0;
	}

	std::cout << '\n';
}
