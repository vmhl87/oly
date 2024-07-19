// Good Influencers  -  https://dmoj.ca/problem/ccc22s5
// ccc 22 s5
//
// We can represent the tree of children as a network of
// "lights", which are either "lit", taking some cost,
// or not. Some lights are "sources". Lights can only
// be lit if they are sources or if some path between
// them and a source is fully lit. We wish to light some
// number of lights such that each light is either lit
// or adjacent to one that is lit.
//
// Tree DP!!!
// For each light n, store four costs:
// 1. Min cost to satisfy n's subtree such that n is lit
//    but is sourced from a node not in its subtree
// 2. n is lit and sourced from node in subtree
// 3. n is unlit and needs parent to be lit
// 4. n is unlit but doesn't require parent to be lit; its
//    subtree is satisfied
//
// Propagation is not that hard.

#include <iostream>
#include <vector>

using LL = long long;

int n, cost[200000], y[200000];
std::vector<int> adj[200000];
LL dp[200000][4];  // 0: lit, needs external
				   // 1: lit, sufficient
				   // 2: unlit, needs
				   // 3: unlit, sufficient

// some states are not possible to reach, so we can cheat and
// replace it with a giant number that is > sum of all costs;
// will result in this state never being chosen
const LL BIG = 200000000;

void dfs(int i, int p){
	for(int x : adj[i]) if(x != p) dfs(x, i);

	// cost of lighting self
	dp[i][0] += cost[i], dp[i][1] += cost[i];

	// check if source
	if(y[i]){
		// if lit, can have children of any state
		for(int x : adj[i]) if(x != p)
			dp[i][0] += std::min(std::min(dp[x][0], dp[x][1]),
								 std::min(dp[x][2], dp[x][3]));
		dp[i][1] = dp[i][0];

		// if not lit, can only choose children that are satisfied
		// (doesn't depend on parent to light/source)
		for(int x : adj[i]) if(x != p)
			dp[i][2] += std::min(dp[x][1], dp[x][3]);
		dp[i][3] = dp[i][2];
	
	// isn't a source
	}else{
		// check for leaves; they by definition can't be sufficient,
		// if they aren't sources
		if(adj[i].size() - (p == -1 ? 0 : 1) == 0)
			dp[i][1] = BIG, dp[i][3] = BIG;

		// if lit and needs external: children can be every state
		// EXCEPT lit and sufficient - if a child is lit and sufficient,
		// it will make current node sufficient
		for(int x : adj[i]) if(x != p)
			dp[i][0] += std::min(std::min(dp[x][2], dp[x][3]),
								 dp[x][0]);

		// if lit and sufficient: must be lit by some child that is
		// itself sufficient - choose the optimal one
		int opt = 0;
		LL delta = 0;
		for(int x : adj[i]) if(x != p){
			// can accept any state, though, so pick by default the
			// lowest cost, and find which node is optimal to make the
			// "sourcing" node
			LL curr = std::min(std::min(dp[x][0], dp[x][1]),
							   std::min(dp[x][2], dp[x][3]));
			dp[i][1] += curr;
			// sometimes a child is still optimal when sourcing, check
			// for this
			if(dp[x][1] == curr) opt = 1;
			else{
				LL next = dp[x][1] - curr;
				if(delta == 0 || next < delta) delta = next;
			}
		}
		if(!opt) dp[i][1] += delta;

		// for all unlit nodes, children MUST be fully sufficient
		// as no "source" can "connect" to a child through unlit node

		// if unlit and needs parent to light: no child can be lit
		for(int x : adj[i]) if(x != p)
			dp[i][2] += dp[x][3];

		// if unlit and sufficient: at least one child must light
		// (as all children must be sufficient this will hold)
		opt = 0, delta = 0;
		for(int x : adj[i]) if(x != p){
			LL curr = std::min(dp[x][1], dp[x][3]);
			dp[i][3] += curr;
			if(dp[x][1] == curr) opt = 1;
			else{
				LL next = dp[x][1] - curr;
				if(delta == 0 || next < delta) delta = next;
			}
		}
		if(!opt) dp[i][3] += delta;
	}
}

int main(){
	std::cin >> n;

	for(int i=1; i<n; ++i){
		int a, b; std::cin >> a >> b, --a, --b;
		adj[a].push_back(b), adj[b].push_back(a);
	}

	for(int i=0; i<n; ++i){
		char c; std::cin >> c;
		y[i] = c=='Y';
	}

	for(int i=0; i<n; ++i) std::cin >> cost[i];

	dfs(0, -1);

	// debug etc
	for(int i=0; i<n; ++i) std::cout << (i+1)%10 << " \n"[i==n-1];
	for(int i=0; i<4; ++i)
		for(int j=0; j<n; ++j){
			if(dp[j][i] >= BIG) std::cout << '-';
			else std::cout << dp[j][i];
			std::cout << " \n"[j==n-1];
		}

	std::cout << std::min(dp[0][1], dp[0][3]) << '\n';
}
