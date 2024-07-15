#pragma GCC optimize("O3")

#include <iostream>
#include <vector>

#define N 200001
 
std::vector<int> tree[N];
int start[N], stop[N], par[N], depth[N];
int n;
int euler = 0;

void dfs(int v, int d) {
    start[v] = euler, depth[v] = d++, ++euler;

    for(int x : tree[v]) dfs(x, d);

    stop[v] = euler;
}

int seg[400001];

int ans;

inline void cmp(int v){
	if(depth[v] < depth[ans]) ans = v;
}

inline int comp(int u, int v) {
    return depth[v] < depth[u] ? v : u;
}

int main() {
	std::cin.tie(0) -> sync_with_stdio(0);
    int q; std::cin >> n >> q;

    for(int i=1; i!=n; i++){
        int b; std::cin >> b, --b;
        tree[b].push_back(i);
        par[i] = b;
    }

    dfs(0, 0);

    for(int i=0; i!=n; ++i) seg[start[i] + n] = i;
    for(int i=n-1; i; --i) seg[i] = comp(seg[i<<1], seg[i<<1|1]);

	while(q--){
        int a, b; std::cin >> a >> b, --a, --b;

		if(start[b] < start[a]) a ^= b, b ^= a, a ^= b;

        if(stop[a] >= stop[b]){
			std::cout << a+1 << '\n';
			continue;
		}

		ans = seg[start[a]+n];

		for(int l = start[a]+n, r = start[b]+n+1; l != r; l >>= 1, r >>= 1){
			if(l&1) cmp(seg[l++]);
			if(r&1) cmp(seg[--r]);
		}

		std::cout << par[ans] + 1 << '\n';
    }
}
