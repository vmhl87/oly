#include <algorithm>
#include <iostream>
#include <array>

using ll = long long;
const int N = 2e5;

std::array<int, 3> e[N];

int root[N+1], a[N+1], b[N+1];

int find(int i){
	if(root[i] == i) return i;
	return root[i] = find(root[i]);
}

bool same(int a, int b){
	return find(a) == find(b);
}

void merge(int u, int v){
	a[v] += a[u];
	b[v] += b[u];
	root[u] = v;
}

int main(){
	int n, m, k; std::cin >> n >> m >> k;

	for(int i=0; i<m; ++i)
		std::cin >> e[i][1] >> e[i][2] >> e[i][0];

	std::sort(e, e+m);

	for(int i=1; i<=n; ++i) root[i] = i;

	for(int i=0; i<k; ++i){
		int x; std::cin >> x;
		++a[x];
	}

	for(int i=0; i<k; ++i){
		int x; std::cin >> x;
		++b[x];
	}

	ll res = 0;

	for(int i=0; i<m; ++i){
		int w = e[i][0],
			u = e[i][1],
			v = e[i][2];

		if(same(u, v)) continue;

		u = find(u), v = find(v);

		ll x = std::min(a[u], b[v]);
		a[u] -= x, b[v] -= x;
		res += x*w;

		x = std::min(a[v], b[u]);
		a[v] -= x, b[u] -= x;
		res += x*w;

		merge(u, v);
	}

	std::cout << res << '\n';
}
