// Longest Flight Route  -  https://cses.fi/problemset/task/1680/
// We can solve this by performing dp on paths: The longest path from
// vertex A to vertex B is the maximum length of a path from A to a
// parent of B, plus one.

#include <functional>
#include <iostream>
#include <vector>
#include <deque>
#include <array>

int main(){
	// fastio
	std::cin.tie(0) -> sync_with_stdio(0);

	int n, m; std::cin >> n >> m;
	
	// store reverse adjacencies; we don't actually care about which
	// nodes *lead to* other ones, but rather, which nodes are the parents
	// of others
	std::vector<int> adj[n];
	for(int i=0; i<m; ++i){
		int a, b; std::cin >> a >> b;
		adj[b-1].push_back(a-1);
	}

	// keep track of length and parent in arrays
	int len[n] = {1}, back[n];

	// determine length of longest path from root to i
	std::function<int(int)> longest = [&](int i){
		if(len[i]) return len[i]-1;

		// find longest path to any of node's parents
		int next = -1, best = -1;
		for(int x : adj[i]){
			int w = longest(x);
			if(w > next) next = w, best = x;
		}

		// process case where no valid path from root exists
		if(next == -1){
			len[i] = -1;
			return -2;
		}

		// longest path = longest path from root to parent, plus one
		++next;

		// write to dp arrrays
		len[i] = next+1, back[i] = best;
		return next;
	};

	// find final path length
	int fi = longest(n-1);

	// negative length signifies no valid path from root
	if(fi < 0){
		std::cout << "IMPOSSIBLE\n";
		return 0;
	}

	// print out backtraced path:
	std::cout << fi+1 << '\n';

	// use `back` array to retrieve path and use stack to reverse
	std::deque<int> trace; trace.push_back(n-1);
	do{
		trace.push_back(back[trace.back()]);
	}while(trace.back() != 0);

	while(trace.size()) std::cout << trace.back()+1 << ' ', trace.pop_back();
	std::cout << '\n';
}
