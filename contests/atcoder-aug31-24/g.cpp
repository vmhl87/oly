#include <iostream>
#include <vector>
#include <array>

using ll = long long;

std::vector<std::array<int, 2>> adj[200000];
int start[200000], end[200000], tour[200000], now;
std::array<int, 2> par[200000];
std::array<ll, 2> tree[800000];
ll depth[200000];
int n;

void dfs(int i, int p){
	tour[now] = i;
	start[i] = now++;
	for(const auto &[x, c] : adj[i]) if(x != p){
		depth[x] = depth[i] + c;
		par[x] = {i, c};
		dfs(x, i);
	}
	end[i] = now;
}

void build(int i, int l, int r){
	if(l==r) tree[i] = {depth[tour[l]], tour[l]};
	else{
		int m = (l+r)/2;
		build(i*2, l, m);
		build(i*2+1, m+1, r);
		tree[i] = std::max(tree[i*2], tree[i*2+1]);
	}
}

ll lazy[800000];

void push(int i){
	lazy[i*2] += lazy[i];
	lazy[i*2+1] += lazy[i];
	lazy[i] = 0;
}

void update(int lb, int rb, int v, int i, int l, int r){
	if(lb>rb) return;
	if(l==lb&&r==rb) lazy[i] -= v;
	else{
		push(i);
		int m = (l+r)/2;
		update(lb, std::min(rb, m), v, i*2, l, m);
		update(std::max(lb, m+1), rb, v, i*2+1, m+1, r);
		if(tree[i*2][0]+lazy[i*2] > tree[i*2+1][0]+lazy[i*2+1])
			tree[i] = tree[i*2], tree[i][0] += lazy[i*2];
		else tree[i] = tree[i*2+1], tree[i][0] += lazy[i*2+1];
	}
}

void fix(int i){
	if(i==0) return;
	if(par[i][1]) fix(par[i][0]);
	// decrease whole subtree of i
	// with par[i][1]
	update(start[i], end[i]-1, par[i][1], 1, 0, n-1);
	par[i][1] = 0;
}

int main(){
	std::cin >> n;
	for(int i=1; i!=n; ++i){
		int a, b, c; std::cin >> a >> b >> c, --a, --b;
		adj[a].push_back({b, c}), adj[b].push_back({a, c});
	}

	dfs(0, -1);

	build(1, 0, n-1);

	ll ans = 0;

	for(int i=0; i!=n; ++i){
		auto [len, x] = tree[1]; len += lazy[1];
		ans += len*2;
		// decrease all paths to x
		fix(x);
		std::cout << ans << '\n';
	}
}
