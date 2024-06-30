// Tree Distances II  -  https://cses.fi/problemset/task/1133/
//
// Very similar approach to standard Tree Distances. However, traversal
// is done with a dfs + bfs rather than a double dfs, mostly because of
// the following: when finding just the maximum path, our solution could
// get away with considering some paths twice. When counting the sum of
// distances, we can't repeat over paths. Because our ext[] propagation
// occurs from parent to all of the children at once, bfs is easier.

#include <iostream>
#include <queue>
#include <stack>


int main(){
	int n; std::cin >> n;

	std::stack<int> adj[n], bdj[n];

	for(int i=1; i<n; ++i){
		int a, b; std::cin >> a >> b, --a, --b;

		adj[a].push(b), adj[b].push(a);
	}

	bool vis[n] = {};
	std::stack<int> dfs;
	dfs.push(0), vis[0] = 1;

	long long child[n] = {};
	int childc[n] = {};

	// dfs only counts subtree size and sum
	while(dfs.size()){
		int t = dfs.top();

		if(adj[t].size()){
			int next = adj[t].top(); adj[t].pop();

			if(!vis[next]){
				// re-add edges to the queue for bfs
				vis[next] = 1, bdj[t].push(next);

				dfs.push(next);
			}

		}else{
			dfs.pop();

			if(dfs.size()){
				childc[dfs.top()] += childc[t]+1;
				child[dfs.top()] += child[t] + childc[t]+1;
			}
		}
	}
	
	std::queue<int> bfs; bfs.push(0);

	// compute size and sum of ext compoment
	long long ext[n] = {};
	int exts[n] = {};

	while(bfs.size()){
		int t = bfs.front(); bfs.pop();

		// Essentially here we need to compute each of the ext[]
		// counts and sums for node t's children.
		// Recall that ext[] propagates from two places:
		//   1. The ext[] of the root
		//   2. The subtrees of the other children
		// First we traverse the children in both directions to
		// propagate all of their subtree computations to each
		// others' ext[] values. Then we overlay the root's ext[]
		// onto the children.

		// component (all children previously traversed) sum & size
		long long comp = 0;
		int count = 0;

		// traverse both ways - invert the stack trivially
		for(int i=0; i<2; ++i){
			std::queue<int> rev;

			while(bdj[t].size()){
				int c = bdj[t].top();
				// rotate 1
				rev.push(c), bdj[t].pop();

				// propagation
				ext[c] += comp;
				exts[c] += count;
				comp += child[c] + 2 + 2*childc[c];
				count += childc[c] + 1;
			}

			// rotate 2
			while(rev.size()) bdj[t].push(rev.front()), rev.pop();

			comp = 0, count = 0;
		}

		// push children to bfs queue & overlay root ext[]
		while(bdj[t].size()){
			int c = bdj[t].top(); bdj[t].pop();

			ext[c] += ext[t] + 1 + exts[t];
			exts[c] += exts[t] + 1;
			bfs.push(c);
		}
	}

	// all paths from node i must be in one of: i's subtree, i's ext[]
	for(int i=0; i<n; ++i)
		std::cout << child[i] + ext[i] << " \n"[i==n-1];
}
