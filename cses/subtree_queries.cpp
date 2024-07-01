// Subtree Queries  -  https://cses.fi/problemset/task/1137/
// pretty standard euler tour problem

#include <iostream>
#include <stack>

typedef long long LL;

int main(){
	int n, q; std::cin >> n >> q;

	int weight[n];
	for(int i=0; i<n; ++i) std::cin >> weight[i];

	std::stack<int> adj[n];

	for(int i=1; i<n; ++i){
		int a, b; std::cin >> a >> b, --a, --b;

		adj[a].push(b), adj[b].push(a);
	}

	// location in tour
	int loc[n][2], p = 1;

	// dfs to order
	bool vis[n] = {};
	std::stack<int> dfs;
	dfs.push(0), vis[0] = 1, loc[0][0] = 0;

	while(dfs.size()){
		int t = dfs.top();

		if(adj[t].size()){
			int next = adj[t].top(); adj[t].pop();

			// set location at push
			if(!vis[next]){
				vis[next] = 1, dfs.push(next);

				loc[next][0] = p++;
			}

		// and at pop
		}else dfs.pop(), loc[t][1] = p;
	}

	// build segtree
	LL tree[n<<1];
	for(int i=0; i<n; ++i) tree[loc[i][0] + n] = weight[i];
	for(int i=n-1; i; --i) tree[i] = tree[i<<1] + tree[i<<1|1];

	while(q--){
		int t; std::cin >> t;

		// update query
		if(t & 1){
			int s, x; std::cin >> s >> x;

			s = n+loc[s-1][0], x -= tree[s];

			for(; s; s >>= 1) tree[s] += x;

		// range query
		}else{
			int s; std::cin >> s;

			int l = n+loc[s-1][0], r = n+loc[s-1][1];

			LL res = 0;

			for(; l < r; l >>= 1, r >>= 1){
				if(l & 1) res += tree[l++];
				if(r & 1) res += tree[--r];
			}

			std::cout << res << '\n';
		}
	}
}
