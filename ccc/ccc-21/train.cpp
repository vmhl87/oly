#include <iostream>
#include <vector>

int n, d[200000], tr[200000], ro[200000];
std::vector<int> adj[200000];
int tree[400000];
bool vis[200000];

void upd(int i, int v){
	tree[i+n] += v;
	for(i = (i+n)/2; i; i /= 2)
		tree[i] = std::min(tree[i<<1], tree[i<<1|1]);
}

int main(){
	int w, q; std::cin >> n >> w >> q;

	for(int i=0; i<w; ++i){
		int a, b; std::cin >> a >> b, --a, --b;
		adj[b].push_back(a);
	}

	vis[n-1] = 1;
	std::vector<int> bfs; bfs.reserve(n), bfs.push_back(n-1);
	int p = 0;
	while(p < bfs.size()){
		int x = bfs[p++];
		for(int i : adj[x]) if(!vis[i])
			vis[i] = 1, bfs.push_back(i), d[i] = d[x]+1;
	}
	for(int i=0; i<n-1; ++i) if(!d[i]) d[i] = n;

	for(int i=0; i<n; ++i){
		int x; std::cin >> x, --x;
		ro[i] = x, tr[x] = i;
	}

	for(int i=0; i<n; ++i) tree[i+n] = tr[i] + d[i];
	for(int i=n-1; i; --i) tree[i] = std::min(tree[i<<1], tree[i<<1|1]);

	while(q--){
		int a, b; std::cin >> a >> b, --a, --b;
		std::swap(ro[a], ro[b]);
		a = ro[a], b = ro[b];
		int delta = tr[a] - tr[b];
		std::swap(tr[a], tr[b]);

		upd(b, delta), upd(a, -delta);

		int best = tr[n-1] - tr[0];
		best = std::min(best, tree[1]);
		// for(int i=0; i<n; ++i)
			// best = std::min(best, tr[i] + d[i]);

		std::cout << best << '\n';
	}
}
