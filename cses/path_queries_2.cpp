#include <iostream>
#include <vector>

const int maxn = 2e5;

std::vector<int> adj[maxn];
int heavy[maxn], jmp[maxn], dep[maxn];

int dfs(int i, int p){
	int sum = 1, best = 0, idx = 0;
	for(int x : adj[i]) if(x != p){
		jmp[x] = i, dep[x] = dep[i] + 1;
		int part = dfs(x, i);
		if(part > best) best = part, idx = x;
		sum += part;
	}

	if(best*2 >= sum) heavy[i] = idx + 1;
	return sum;
}

int rmq[maxn*2], v[maxn], n;
int idx[maxn], top[maxn], pos;

void dfs2(int i, int p, int o){
	idx[i] = pos;
	top[i] = o;
	++pos;

	if(heavy[i]) dfs2(heavy[i]-1, i, o);

	for(int x : adj[i]) if(x != p && x != heavy[i]-1)
		dfs2(x, i, x);
}

void set(int i, int v){
	rmq[i+n] = v;

	for(i=(i+n)/2; i; i/=2)
		rmq[i] = std::max(rmq[i*2], rmq[i*2+1]);
}

int range(int l, int r){
	int res = rmq[r+n];
	for(l += n, r += n; l < r; l /= 2, r /= 2){
		if(l&1) res = std::max(res, rmq[l++]);
		if(r&1) res = std::max(res, rmq[--r]);
	}
	return res;
}

int query(int a, int b){
	int res = 0;
	while(top[a] != top[b]){
		if(dep[top[b]] > dep[top[a]]) std::swap(a, b);
		res = std::max(res, range(idx[top[a]], idx[a]));
		a = jmp[top[a]];
	}
	if(dep[b] > dep[a]) std::swap(a, b);
	return std::max(res, range(idx[b], idx[a]));
}

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);
	
	int q; std::cin >> n >> q;

	for(int i=0; i<n; ++i) std::cin >> v[i];

	for(int i=1; i<n; ++i){
		int a, b; std::cin >> a >> b;
		adj[--a].push_back(--b);
		adj[b].push_back(a);
	}

	dfs(0, 0), dfs2(0, 0, 0);

	for(int i=0; i<n; ++i) rmq[n+idx[i]] = v[i];
	for(int i=n-1; i; --i) rmq[i] = std::max(rmq[i*2], rmq[i*2+1]);

	while(q--){
		int t, a, b; std::cin >> t >> a >> b;

		if(t&1) set(idx[--a], b);
		else std::cout << query(--a, --b) << " \n"[q==0];
	}
}
