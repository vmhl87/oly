// Planet Queries 2  -  https://cses.fi/problemset/task/1160/
//
// We can extend our previous solution to Planet Queries 1.
//
// Utilizing the binlifting jumps and computed cycles, we first
// equalize the depths of a and b. Then, if they are at depth 0,
// meaning they are on a cycle portion, we check if they are
// part of the same cycle, and if so, compute the number of jumps
// through the cycle necessary to meet.
//
// Refer to https://github.com/vmhl87/usaco/blob/main/cses/planet_queries_1.cpp
// for more comments. The entire first section of this solution is a direct
// copy from my previous solution.

#include <iostream>
#include <vector>
#include <stack>

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int n, q; std::cin >> n >> q;

	int to[n];
	for(int i=0; i<n; ++i) std::cin >> to[i], --to[i];

	// memoized traversal algorithm
	
	int depth[n], jump[n], cyloc[n], cypos[n];
	std::vector<std::vector<int>> cyc;

	bool vis[n] = {};
	for(int i=0; i<n; ++i) if(!vis[i]){
		// extract untraversed cycle path
		std::stack<int> chain; chain.push(i);

		while(!vis[chain.top()])
			vis[chain.top()] = 1, depth[chain.top()] = -1, chain.push(to[chain.top()]);

		// write to cycle vector vector
		if(depth[chain.top()] == -1){
			std::vector<int> cycle;

			cycle.push_back(chain.top()), chain.pop();

			while(chain.top() != cycle[0]) cycle.push_back(chain.top()), chain.pop();

			for(int j=0; j<(int)cycle.size(); ++j)
				depth[cycle[j]] = 0, jump[cycle[j]] = cycle[j],
					cyloc[cycle[j]] = j, cypos[cycle[j]] = cyc.size();

			cyc.push_back(cycle);
		}

		chain.pop();

		// compute binlifting jumps
		while(chain.size()){
			int x = chain.top(); chain.pop();

			depth[x] = depth[to[x]] + 1;

			if(depth[to[x]] + depth[jump[jump[to[x]]]] == depth[jump[to[x]]]<<1)
				jump[x] = jump[jump[to[x]]];
			else jump[x] = to[x];
		}
	}

	// process queries (this is the only portion that is different
	// between my two solutions)
	while(q--){
		int a, b; std::cin >> a >> b, --a, --b;

		// sanity check - because the chains are directed, it is impossible to go
		// from a lower depth to a higher one
		if(depth[b] > depth[a]){
			std::cout << -1 << '\n';
			continue;
		}

		// a will be overwritten, so compute distance beforehand
		int dist = depth[a] - depth[b];

		// Using the binlifting jumps, equalize depth
		while(depth[a] > depth[b]){
			// take the long jump if it will not overshoot b's depth -
			// overshooting is unnacceptable because we are not able to backtrack
			// through the directed chains
			if(depth[jump[a]] < depth[b]) a = to[a];
			else a = jump[a];
		}

		// We must determine if b was reachable from a. Notice that the only planets
		// reachable from a are the planets ahead of it on its own chain, and all of
		// the planets in its ending cycle. By equalizing depth, we can check if a and
		// b are on the same chain.

		// If their depths are both zero, we need to check if they are on the same cycle.
		// Otherwise, if they are not both pointing to the same planet, they must be on
		// different chains.
		if(depth[a] == 0){
			// cypos stores which cycle, cyloc stores location in cycle
			if(cypos[a] != cypos[b]){
				std::cout << -1 << '\n';
				continue;
			}

			// similarly to in our previous solution, where we jumped forward in the
			// cycle in O(1), we can find distances in O(1) with modulus
			std::cout << dist +
				(cyloc[a]-cyloc[b] + (int)cyc[cypos[a]].size()) % cyc[cypos[a]].size()
				<< '\n';
		// if their depths are not zero, they must now be the same planet. Otherwise,
		// b is guaranteed to be unreachable from a.
		}else{
			if(a != b) std::cout << -1;
			else std::cout << dist;
			std::cout << '\n';
		}
	}
}
