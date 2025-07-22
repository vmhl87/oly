// URL: https://codeforces.com/contest/1363/problem/E

#include <iostream>
#include <vector>

using ll = long long;
const int N = 2e5;

int a[N], b[N], c[N], e[N], f[N];
std::vector<int> d[N];
ll res;

void dfs(int i, int p, ll m){
	if(b[i] && !c[i]) ++e[i];
	if(!b[i] && c[i]) ++f[i];

	for(int x : d[i]) if(x != p)
		dfs(x, i, std::min(m, (ll) a[x])),
			e[i] += e[x], f[i] += f[x];

	if(m == a[i]){
		int S = std::min(e[i], f[i]);
		e[i] -= S, f[i] -= S;
		res += m*S*2;
	}
}

int main(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i)
		std::cin >> a[i] >> b[i] >> c[i];

	for(int i=1; i<n; ++i){
		int x, y; std::cin >> x >> y;
		d[--x].push_back(--y);
		d[y].push_back(x);
	}

	{
		int S = 0;
		for(int i=0; i<n; ++i) S += b[i] - c[i];
		if(S != 0) std::cout << "-1\n", exit(0);
	};

	dfs(0, 0, a[0]);

	std::cout << res << '\n';
}
