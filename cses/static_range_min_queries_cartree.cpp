// half-finished approach which represents the array as a
// cartesian tree and uses lowest common ancestor to find
// minimum value within a range
//
// ends up being slower than segtree

#include <iostream>
#include <array>
#include <stack>

int main(){
	int n, q; std::cin >> n >> q;

	// build the cartesian tree in-place by storing for
	// each element its parent and depth
	std::array<int, 3> a[n];
	// similarly to convex hull, but without convexity check,
	// we store a stack of the "sweeping hull"
	std::stack<int> s;
	int root = 0;

	for(int i=0; i<n; ++i){
		std::cin >> a[i][0];
		
		// the "sweeping hull" must always be increasing in depth
		// so if our current node is smaller than the top of the
		// hull we pop that value off of the hull
		int last = -1;
		while(s.size() && a[i][0] < a[s.top()][0]) last = s.top(), s.pop();
		// reconnect popped-off sections of the sweeping hull by
		// their root node (last node popped off)
		if(last > -1) a[last][1] = i;

		// determine parent of this node
		if(s.size()) a[i][1] = s.top();
		else a[i][1] = -1, root = i;

		// this new point must necessarily be on the sweeping hull
		s.push(i);
	}

	// stack adjacencies for dfs
	std::stack<int> adj[n];
	for(int i=0; i<n; ++i)
		if(a[i][1] > -1) adj[a[i][1]].push(i);

	// dfs to find depth of each element of the array
	std::stack<int> dfs;
	dfs.push(root);
	while(dfs.size()){
		int t = dfs.top();
		if(adj[t].size()) dfs.push(adj[t].top()), adj[t].pop();
		else a[t][2] = dfs.size(), dfs.pop();
	}

	// answer queries
	while(q--){
		int l, r; std::cin >> l >> r, --l, --r;

		// if one element is lower in the tree than the other,
		// push it upward until equal depth
		while(a[l][2] > a[r][2]) l = a[l][1];
		while(a[l][2] < a[r][2]) r = a[r][1];

		// push up to find common ancestor
		while(l != r) l = a[l][1], r = a[r][1];

		std::cout << a[l][0] << '\n';
	}
}
