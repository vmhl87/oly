// Wonderful Tree  -  https://codeforces.com/contest/1987/problem/E
//
// We can make some observations to simplify this problem:
//
//   1. For some non-wonderful node X, we can define its delta as
//      the difference between its value and the sum of its childrens'
//      values. This delta must be added to some selection of its
//      children. If this violates the wonderfulness of any of said
//      children, this delta will needed to be added to 2-degree children,
//      etc.
//      
//   2. It is suboptimal to propagate a node's delta a distance longer
//      than the distance from X to the closest leaf of its subtree.
//      Therefore, the cost of making some node wonderful is at most its
//      delta * the distance to its closest leaf.
//
//   3. If a node has a value smaller than the sum of its children, it can
//      neutralize some amount of incoming delta without violating.
//
//   4. Define an "endpoint" as any node that can neutralize nonzero delta
//      without violating. Every leaf is an endpoint, and each node with
//      smaller value than child sum is an endpoint until it is used up.
//      The cost of equalizing a delta to an endpoint is delta * distance
//      between node and endpoint.
//
//   5. For a non-wonderful node X, if its subtree has already been made
//      wonderful, it is optimal to continually pass its delta down to
//      the nearest endpoint. If said endpoint is used up, switch to the
//      next nearest endpoint, and continue until the delta has been fully
//      accounted for.
//
// We can solve the problem by DP:  For each node, fix its subtree, and
// compute all endpoints in it. Then, reduce its delta by passing to its
// endpoints.
//
// My implementation uses a DFS traversal to fix the subtree and compute
// its endpoints before processing each node. Endpoints are stored using
// a frequency map; as we don't care about the location of the endpoint,
// my solution stores only the amount of delta that can be equalized by
// endpoints at each distance. The DFS traversal also enables the maps of
// children to be used to compute maps of parents easily.

#include <iostream>
#include <stack>
#include <map>

typedef long long LL;

void test_case(){
	int n; std::cin >> n;
	LL a[n]; for(int i=0; i<n; ++i) std::cin >> a[i];
	std::stack<int> adj[n];

	for(int i=1; i<n; ++i){
		int b; std::cin >> b;
		adj[b-1].push(i);
	}

	std::stack<int> dfs;
	// shortest path from node to leaf
	int shortest[n] = {};
	// result, running sum of children
	LL res = 0, sum[n] = {};
	bool leaf[n] = {};
	for(int i=0; i<n; ++i) if(!adj[i].size()) leaf[i] = 1;
	// mapping from distance -> capacity of all sub-endpoints at distance
	std::map<int, LL> free[n];

	dfs.push(0);

	while(dfs.size()){
		int t = dfs.top();

		if(adj[t].size()) dfs.push(adj[t].top()), adj[t].pop();
		else{
			// leaves don't need to be processed because they are always
			// going to be wonderful, and aren't temporal endpoints
			if(!leaf[t]){
				// if node is smaller than child sum it is endpoint
				if(a[t] < sum[t]){
					free[t][0] = sum[t] - a[t];

				// otherwise, put its delta somewhere
				}else if(a[t] > sum[t]){
					LL diff = a[t] - sum[t];

					// consider endpoints, starting from closest
					while(free[t].size()){
						auto x = free[t].begin();

						// if there is a leaf that is better than this
						// endpoint just take the leaf
						if(x->first > shortest[t]) break;

						// if delta is bigger than capacity of endpoint,
						// remove endpoint, calculate cost, update delta
						if(diff > x->second){
							diff -= x->second;
							res += (LL)x->first * x->second;
							free[t].erase(x->first);

						// otherwise, reduce capacity of endpoint, compute
						// cost, and reset delta
						}else{
							free[t][x->first] -= diff;
							res += diff * x->first;
							diff = 0;
							break;
						}
					}

					// if leftover delta (or we broke out) then take
					// closest leaf and give all remaining delta
					if(diff) res += diff * shortest[t];
				}
			}
			dfs.pop();
			if(dfs.size()){
				int x = dfs.top();

				// update shortest path to leaf of parent
				if(!shortest[x] || shortest[t]+1 < shortest[x])
					shortest[x] = shortest[t]+1;

				// update parent sum
				sum[x] += a[t];

				// update parent endpoint mapping and clear own
				for(const auto &[k, v] : free[t]){
					// if endpoint is worse than leaf, don't include
					// endpoint for performance reasons
					if(k+1 >= shortest[x]) break;
					free[x][k+1] += v;
				}
				free[t].clear();
			}
		}
	}

	std::cout << res << '\n';
}

int main(){
	int t; std::cin >> t;

	while(t--) test_case();
}
