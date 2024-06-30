// Tree Distances  -  https://cses.fi/problemset/task/1132/
//
// We root the tree at vertex 1, and then compute for each node
// two values: the height of its subtree, and the longest "external
// path" - a path that starting from node i, goes "up" from node i,
// through its parent, and does not pass through its subtree.
//
// Consider for example the sample tree:
//
//                                1
//                               / \
//                              3   2
//                             / \
//                            5   4
//
// The heights are quite obvious - {2, 0, 1, 0, 0}.
// ext is {0, 3, 2, 3, 3} - node 1 obviously has no paths leading to
// its parent, as it has no parent. Node 2 has an "external path" of
// length 3: 2 -> 1 -> 3 -> 5. Similarly, the longest ext of 3 is
// 3 -> 1 -> 2.
//
// If we can efficiently compute height[] and ext[] for the tree,
// determining the longest path from any node is easy. We can trivially
// see that from any node i, its longest path to another node j must
// be either through i's subtree, or through i's parent.
//
// Computing heights of subtrees is easy with a dfs. Computing ext is
// slightly harder. However, we can sort of do dp:
// 
//    Consider the ext of vertex 4. It must pass upwards to vertex 3,
//    but then what next? Either it continues to pass up from 3, or it
//    descends down from 3 to 5.
//
// We can see that the ext of any node i must be derived from either
// the ext of its parent, or the height of its parent's subtree.
// 
// So, to compute ext, we can simply use the dfs order:
//
//    When dfs'ing to a new vertex, compute its ext as either:
//      1 more than its parent's ext
//      1 more than its parent's height
//
// We do need to dfs twice to cover both orderings of the children.

#include <iostream>
#include <stack>
#include <cmath>

int main(){
	int n; std::cin >> n;

	// adjacencies and reverse, for both dfs'es
	std::stack<int> adj[n], bdj[n];

	for(int i=1; i<n; ++i){
		int a, b; std::cin >> a >> b, --a, --b;

		adj[a].push(b), adj[b].push(a);
	}

	bool vis[n] = {};
	std::stack<int> dfs; dfs.push(0), vis[0] = 1;

	int height[n] = {}, ext[n] = {};

	// first dfs in normal order
	while(dfs.size()){
		int t = dfs.top();

		// consider adding next child
		if(adj[t].size()){
			int next = adj[t].top(); adj[t].pop();

			if(!vis[next]){
				vis[next] = 1;
				// refill bdj - because it is a stack,
				// it will reverse order for us
				dfs.push(next), bdj[t].push(next);

				// update ext
				ext[next] = std::max(ext[next], height[t]+1);
				ext[next] = std::max(ext[next], ext[t]+1);
			}

		}else{
			dfs.pop();

			// update heights
			if(dfs.size()) height[dfs.top()] = std::max(
					height[dfs.top()], height[t]+1
				);
		}
	}

	// reset partial heights for second pass
	dfs.push(0);
	for(int i=0; i<n; ++i) height[i] = 0;

	// second dfs in reverse order
	while(dfs.size()){
		int t = dfs.top();

		if(bdj[t].size()){
			int next = bdj[t].top(); bdj[t].pop();

			// don't need to check for visited because we have
			// already pruned the back-parent edges
			dfs.push(next);

			// update with new partial heights (other side of tree)
			// and also fully computed ext
			ext[next] = std::max(ext[next], height[t]+1);
			ext[next] = std::max(ext[next], ext[t]+1);

		}else{
			dfs.pop();

			if(dfs.size()) height[dfs.top()] = std::max(
					height[dfs.top()], height[t]+1
				);
		}
	}

	// compute
	for(int i=0; i<n; ++i)
		std::cout << std::max(ext[i], height[i]) << " \n"[i==n-1];
}
