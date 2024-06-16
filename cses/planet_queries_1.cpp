// Planet Queries 1  -  https://cses.fi/problemset/task/1750/
//
// We can break down this task into some subtasks:
//
// 1. Determine all of the cycles in the graph, and compute for
//    each node the number of jumps it has until it hits a cycle.
//    This is quite similar to the approach used in Planet Cycles.
//
// 2. Within the "chain" of planets from some arbitrary node n to
//    the earliest point in a cycle, implement an algorithm to
//    efficiently jump to any point in the chain in less than O(n).
//
// 3. Store the cycles in a structure that permits jumping any
//    arbitrary distance within the cycle in O(1).
//
// Task 1 can be accomplished using memoization.
//
// For task 2 we can use binary lifting to jump a distance k in
// O(log k) operations.
//
// We can store each cycle as an array, where each element jumps to
// its right adjacent element, with wraparounds. Then, store for
// each node in the cycle its position in this array. Such a structure
// meets the O(1) requirement.
//
// Implementation isn't too bad, though it is pretty long.

#include <iostream>
#include <vector>
#include <stack>

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int n, q; std::cin >> n >> q;

	int to[n];
	for(int i=0; i<n; ++i) std::cin >> to[i], --to[i];

	// jump is for binlifing, cyloc and cypos are for location in cycle array and
	// which cycle array in vector vector, respectively
	int depth[n], jump[n], cyloc[n], cypos[n];
	// cyc does what it looks like - stores all of the cycles
	std::vector<std::vector<int>> cyc;

	// visited and depth arrays are all we need for memoization
	bool vis[n] = {};
	for(int i=0; i<n; ++i) if(!vis[i]){
		// this section is very similar to https://github.com/vmhl87/usaco/blob/main/cses/planets_cycles.cpp
		std::stack<int> chain; chain.push(i);

		// temporarily mark depth with -1 (this is necessary for differentiation
		// between a path that hits a previously computed section and a path that finds
		// a cycle)
		while(!vis[chain.top()])
			vis[chain.top()] = 1, depth[chain.top()] = -1, chain.push(to[chain.top()]);

		if(depth[chain.top()] == -1){
			// unlike in planet queries, we want to store the cycle in the vector vector
			std::vector<int> cycle;

			cycle.push_back(chain.top()), chain.pop();

			while(chain.top() != cycle[0]) cycle.push_back(chain.top()), chain.pop();

			// for every element of the cycle update its cycle location and cycle position
			for(int j=0; j<(int)cycle.size(); ++j)
				depth[cycle[j]] = 0, jump[cycle[j]] = cycle[j],
					cyloc[cycle[j]] = j, cypos[cycle[j]] = cyc.size();

			cyc.push_back(cycle);
		}

		chain.pop();

		// update rest of chain and use binlifting jumps for O(log n) traverse
		while(chain.size()){
			int x = chain.top(); chain.pop();

			depth[x] = depth[to[x]] + 1;

			// skew binary jump structure
			if(depth[to[x]] + depth[jump[jump[to[x]]]] == depth[jump[to[x]]]<<1)
				jump[x] = jump[jump[to[x]]];
			else jump[x] = to[x];
		}
	}

	// process queries!
	while(q--){
		int x, k; std::cin >> x >> k, --x;

		// check if we reach a cycle portion
		if(k > depth[x]){
			k -= depth[x];

			// to quickly reach the end of the chain, repeatedly take
			// the jumps - none of them will ever go past the end
			while(depth[x]) x = jump[x];

			// because of the way we push nodes onto the cycle vector, they
			// end up being reversed - so instead of adding the number of jumps
			// to the node's location in the array, we subtract it, and use modulo
			// so that the index is positive
			int idx = (cyloc[x]-k) % (int)cyc[cypos[x]].size();
			if(idx < 0) idx += (int)cyc[cypos[x]].size();

			std::cout << cyc[cypos[x]][idx]+1 << '\n';
		// if we don't reach a cycle position, just jump through the chain
		}else{
			// store the target depth in k
			k = depth[x] - k;

			while(depth[x] > k){
				// if the current node's jump goes past the target,
				// do a normal step forward, otherwise use the jump
				if(depth[jump[x]] < k) x = to[x];
				else x = jump[x];
			}

			std::cout << x+1 << '\n';
		}
	}
}
