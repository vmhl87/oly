// Planets Cycles  -  https://cses.fi/problemset/task/1751/
// We can use a DP type approach here, storing the length until
// repeated visit in a way that we don't need to recompute for any
// individual note. This guarantees O(n).

#include <iostream>
#include <stack>

int main(){
	int n; std::cin >> n;

	int to[n];
	for(int i=0; i<n; ++i) std::cin >> to[i], --to[i];

	// store results in array for memoization - values are init to
	// 0, so we can tell if we have computed each node before,
	// eliminating the need for another visited array
	int res[n] = {};
	for(int i=0; i<n; ++i){
		if(i) std::cout << ' ';

		// chain of visited planets from i to either a repeated visit
		// or a node we have already computed
		std::stack<int> vis; vis.push(i);

		// instead of using a separate visited set/array, we can mark
		// in the result array with a -1
		while(res[vis.top()] == 0){
			res[vis.top()] = -1;
			vis.push(to[vis.top()]);
		}

		// note that our chain of visited planets will *end* with a planet
		// which is either already computed or is the first repeated one
		// we find in this chain. For example, in the example, generating
		// the chain from planet 1 will result in 1 -> 2 -> 4 -> 1.

		// if we hit a previously computed node, its result will be fully
		// computed, but if we instead did find a cycle, its result will be
		// -1 to signify partial state.
		if(res[vis.top()] == -1){
			// extract the cycle
			std::stack<int> cyc;

			// root = repeated vertex in cycle
			int root = vis.top(); vis.pop(), cyc.push(root);

			// extract entire cycle from visited chain
			while(vis.top() != root) cyc.push(vis.top()), vis.pop();

			// size of cycle
			int size = cyc.size();

			// each vertex in the cycle will have a result of `size`, as if
			// they move forward by `size` steps they will complete a loop
			while(cyc.size()) res[cyc.top()] = size, cyc.pop();
		}

		// the end of the chain will always be already computed at this point
		// because it the chain either ended when ith it this node or it was
		// part of the cycle that was just computed
		vis.pop();

		// write results of the rest of the chain, if any
		while(vis.size()) res[vis.top()] = res[to[vis.top()]] + 1, vis.pop();

		std::cout << res[i];
	}

	std::cout << '\n';
}
