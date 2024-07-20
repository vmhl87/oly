// New Roads Queries  -  https://cses.fi/problemset/task/2101/
//
// At first, I tried offline processing of queries.
// This doesn't work for a few reasons, namely that there isn't a
// good way to preprocess queries such that after adding each edge,
// constraints can be resolved in less than O(n).
//
// Online queries, on the other hand, were actually somewhat doable.
// Essentially, we need to find a path between two nodes that minimizes
// the maximum "weight" (time until construction) of its edges.
//
// Firstly, it is possible that some edges are not optimal to use.
// Say we have three nodes a, b, c, and the weight between a <-> b
// and b <-> c is 1, and the weight between a <-> c is 2: we should
// therefore never take the path directly from a to c.
// Essentially, we need to generate some MST-like skeleton from the
// graph. Here, it's actually very easy; we can simply add edges in
// order of which roads are built: if the newly created edge connects
// two nodes that are already connected, that new edge must be sub
// optimal, and we don't include in the tree. (this also mantains
// that it is a tree.)
//
// Then, if we have a tree, we can use binlift to find the path between
// a and b and compute the maximally weighted edge in O(log n).

#include <iostream>
#include <vector>
#include <array>

const int MAXN = 200001;

std::vector<std::array<int, 2>> adj[MAXN];

// lin-mem binlifting by computing a single jump along skew
// binary tree - learned this from that one codeforces blog
bool vis[MAXN];
int jump[MAXN][2], par[MAXN][2], depth[MAXN];
void dfs(int i, int p){
	vis[i] = 1;

	for(const auto &[x, t] : adj[i]) if(x != p){
		// parent node & weight to parent
		par[x][0] = i, par[x][1] = t;
		depth[x] = depth[i]+1;

		// compute skew binary tree and balance etc etc
		if(depth[i] + depth[jump[jump[i][0]][0]] == depth[jump[i][0]]*2){
			jump[x][0] = jump[jump[i][0]][0];
			jump[x][1] = std::max(t, std::max(jump[i][1], jump[jump[i][0]][1]));
		}else jump[x][0] = i, jump[x][1] = t;

		dfs(x, i);
	}
}

// unite-by-size dsu
int dsu[MAXN];
int root(int i){
	if(dsu[i] < 0) return i;
	return dsu[i] = root(dsu[i]);
}

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int n, m, q; std::cin >> n >> m >> q;

	for(int i=0; i<n; ++i) dsu[i] = -1;

	// input edges and construct tree simultaneously
	for(int i=0; i<m; ++i){
		int a, b; std::cin >> a >> b, --a, --b;
		int ra = root(a), rb = root(b);

		if(ra == rb) continue;

		// unite by size lol
		if(dsu[ra] < dsu[rb]) dsu[ra] += dsu[rb], dsu[rb] = ra;
		else dsu[rb] += dsu[ra], dsu[ra] = rb;

		adj[a].push_back({b, i});
		adj[b].push_back({a, i});
	}

	// graphs are not always connected...
	for(int i=0; i<n; ++i) if(!vis[i]) dfs(i, -1);

	while(q--){
		int a, b; std::cin >> a >> b, --a, --b;

		// repurpose mst-finding dsu for connected component
		if(root(a) != root(b)){
			std::cout << "-1\n";
			continue;
		}

		int res = -1;

		// swap to keep in order - idk makes it easier
		if(depth[a] < depth[b]) a ^= b, b ^= a, a ^= b;

		// equalize depths
		while(depth[a] > depth[b])
			if(depth[jump[a][0]] < depth[b])
				res = std::max(res, par[a][1]), a = par[a][0];
			else res = std::max(res, jump[a][1]), a = jump[a][0];

		// find lca
		while(a != b)
			if(jump[a][0] != jump[b][0])
				res = std::max(res, std::max(jump[a][1], jump[b][1])),
					a = jump[a][0], b = jump[b][0];
			else res = std::max(res, std::max(par[a][1], par[b][1])),
				a = par[a][0], b = par[b][0];

		std::cout << res+1 << '\n';
	}
}
