#include <iostream>
#include <vector>
#include <array>
#include <queue>

const int N = 1e5;

std::vector<std::array<int, 2>> adj[N];
int r[N], g[N];

int opt[N];
bool v[N];

int main(){
	int n, m; std::cin >> n >> m;
	
	for(int i=0; i<n; ++i) std::cin >> r[i] >> g[i], opt[i] = 1e9+5e8;

	for(int i=0; i<m; ++i){
		int u, v, l; std::cin >> u >> v >> l, --u, --v;
		adj[u].push_back({v, l});
		adj[v].push_back({u, l});
	}

	opt[0] = 0;

	std::priority_queue<std::array<int, 2>> q;

	q.push({0, 0});

	while(q.size()){
		std::array<int, 2> t = q.top();
		q.pop();

		if(v[t[1]]) continue;

		v[t[1]] = 1;

		opt[t[1]] = -t[0];

		if(t[1] != n-1){
			int x = opt[t[1]] % (r[t[1]]+g[t[1]]);
			if(x >= r[t[1]]) opt[t[1]] += r[t[1]]+g[t[1]]-x;
		}

		for(const auto &[u, l] : adj[t[1]])
			if(!v[u]) q.push({-opt[t[1]]-l, u});
	}

	std::cout << opt[n-1] << '\n';
}
