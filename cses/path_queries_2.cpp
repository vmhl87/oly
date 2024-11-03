#include <iostream>
#include <vector>

const int maxn = 2e5;

std::vector<int> adj[maxn];
int heavy[maxn], jmp[20][maxn], dep[maxn];

int dfs(int i, int p){
	int sum = 1, best = 0, idx = 0;
	for(int x : adj[i]) if(x != p){
		jmp[0][x] = i;
		dep[x] = dep[i] + 1;
		int part = dfs(x, i);
		if(part > best) best = part, idx = x;
		sum += part;
	}

	if(best*2 >= sum) heavy[i] = idx + 1;
	return sum;
}

int lca(int a, int b){
	if(dep[b] > dep[a]) std::swap(b, a);

	for(int i=19; i>=0; --i)
		if(dep[jmp[i][a]] >= dep[b])
			a = jmp[i][a];

	if(a == b) return a;

	for(int i=19; i>=0; --i)
		if(jmp[i][a] != jmp[i][b])
			a = jmp[i][a], b = jmp[i][b];

	return jmp[0][a];
}

int idx[maxn], top[maxn], pos;

void dfs2(int i, int p, int o){
	idx[i] = pos;
	top[i] = o;
	++pos;

	if(heavy[i]) dfs2(heavy[i]-1, i, o);

	for(int x : adj[i]) if(x != p && x != heavy[i]-1)
		dfs2(x, i, x);
}

int rmq[maxn*2], v[maxn], n;

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

int climb(int lo, int hi){
	if(top[lo] == top[hi]) return range(idx[hi], idx[lo]);
	return std::max(range(idx[top[lo]], idx[lo]),
			climb(jmp[0][top[lo]], hi));
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

	for(int i=1; i<20; ++i)
		for(int j=0; j<n; ++j)
			jmp[i][j] = jmp[i-1][jmp[i-1][j]];

	for(int i=0; i<n; ++i) rmq[n+idx[i]] = v[i];
	for(int i=n-1; i; --i) rmq[i] = std::max(rmq[i*2], rmq[i*2+1]);

	while(q--){
		int t, a, b; std::cin >> t >> a >> b;

		if(t&1) set(idx[a-1], b);
		else{
			int c = lca(--a, --b);
			std::cout << std::max(climb(a, c), climb(b, c)) << " \n"[q==0];
		}
	}
}
