// Weird bridgefinding algorithm
// Essentially, we traverse graph with a DFS,
// and keep track of back edges. Anytime there
// is a back edge, it "invalidates" all edges
// in the path along the DFS tree. For example:
//
//                   1
//                  / \
//                 2---3
//                     |
//                     4
//
// Say that 2 is traversed before 3. When we get
// to 3, the edge 1 -- 3 will be counted as a back
// edge, and invalidates the edges 1 -- 2 and 2 -- 3.
// 
// To process invalidations, we can use an idea
// similar to difference array. We keep a count of
// back edges that pass over each node, `now`, and
// record which nodes are starting and endings for
// back edges. At any starting of a back edge, increment
// `now`, and at the ending, decrement.

#include <iostream>
#include <vector>

const int MAXN = 100;

std::vector<int> adj[MAXN];

// delta operates like a difference array, `now` counts
// the number of back edges over current node
int depth[MAXN], delta[MAXN], parent[MAXN], now;
bool bridge[MAXN];

void dfs(int i, int p){
	for(int x : adj[i]) if(x != p){
		// untraversed edge
		if(!depth[x]){
			depth[x] = depth[i] + 1, parent[x] = i;
			dfs(x, i);

		// back edge found - update the deltas of
		// both endpoints and do nothing
		}else if(depth[x] < depth[i]){
			++delta[i], --delta[x];
			std::cout << "Back edge: " << i+1 << ' ' << x+1 << '\n';
		}
	}

	// We are done processing node i, so we return along
	// the DFS path to its parent. We here need to
	// process all of the accumulated back edge ends.
	now += delta[i];

	// root node doesn't have a parent, so isn't the
	// lower end of a bridge.
	if(p != -1){
		// check if there are any invalidations by seeing
		// if there are any back edges passing over node
		if(now == 0) bridge[i] = 1;

		// We need to reset `now`. Why? Consider this:
		//          
		//                ->1
		//               /  |
		//              |   2
		//               \ / \
		//                3   4
		// Because of the back edge from 3 to 1, node 3
		// is invalidated. However, it doesn't invalidate
		// node 4. To handle this, we "stash" the current
		// count of back edges at the *parent of 2*, and
		// reset the current count. Then, 4 won't be invalid,
		// but we will still be able to re-invalidate 2.
		delta[p] += now, now = 0;
	}
}

int main(){
	int n, m; std::cin >> n >> m;
	
	for(int i=0; i<m; ++i){
		int a, b; std::cin >> a >> b, --a, --b;
		adj[a].push_back(b), adj[b].push_back(a);
	}

	depth[0] = 1;

	dfs(0, -1);

	std::cout << "Bridges:\n";
	for(int i=0; i<n; ++i) if(bridge[i])
		std::cout << i+1 << " -- " << parent[i]+1 << '\n';
}
