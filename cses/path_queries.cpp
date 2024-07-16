// Path Queries  -  https://cses.fi/problemset/task/1138/
//
// Notice that anytime we update a node n, the only queries
// that change are the nodes in its subtree. Therefore we
// can use euler tour to store nodes in dfs order, and update
// all of a node's children with a segment tree range.
//
// Though we need range updates, we don't need range queries,
// so we can cheese with a lazy noprop segtree

#include <iostream>
#include <vector>

using LL = long long;

// static arrays boing boing
std::vector<int> adj[200001];
int start[200001], end[200001], v[200001], n, e;

LL tree[400002];

// compute euler tour and initial query value in one pass
void dfs(int i, int p, LL d){
	// initialize segtree leaves here, but don't update
	// intermediate - we are using lazy noprop here so inter
	// nodes are only filled by updates
	d += v[i], start[i] = e, tree[e+n] = d, ++e;

	for(int x : adj[i]) if(x != p) dfs(x, i, d);

	end[i] = e;
}

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int q; std::cin >> n >> q;
	for(int i=0; i<n; ++i) std::cin >> v[i];

	for(int i=1; i<n; ++i){
		int a, b; std::cin >> a >> b, --a, --b;
		adj[a].push_back(b), adj[b].push_back(a);
	}

	e = 0;
	dfs(0, -1, 0);

	while(q--){
		int t; std::cin >> t;

		// update query
		if(t&1){
			int s; LL x;
			std::cin >> s >> x, --s;
			// delta
			LL y = x - v[s]; v[s] = x;

			// put all updates in tree, don't worry about prop
			for(int l=start[s]+n, r=end[s]+n; l<r; l>>=1, r>>=1){
				if(l&1) tree[l++] += y;
				if(r&1) tree[--r] += y;
			}
		}else{
			int s; std::cin >> s, --s;

			// walk from node to root and add up all lazy updates
			LL res = 0;
			for(int x=start[s]+n; x; x>>=1)
				res += tree[x];

			std::cout << res << '\n';
		}
	}
}
