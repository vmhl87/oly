#include <iostream>
#include <vector>
#include <queue>

using ll = long long;
const int N = 4e4;

std::vector<int> adj[N];

ll d1[N], d2[N], d3[N];

void bfs(int s, ll *d){
	std::queue<int> bfs;

	bfs.push(s);

	while(bfs.size()){
		int t = bfs.front(); bfs.pop();

		for(int x : adj[t]) if(!d[x] && x != s)
			d[x] = d[t]+1, bfs.push(x);
	}
}

int main(){
	freopen("piggyback.in", "r", stdin);
	freopen("piggyback.out", "w", stdout);

	int b, e, p, n, m; std::cin >> b >> e >> p >> n >> m;

	while(m--){
		int x, y; std::cin >> x >> y;
		adj[--x].push_back(--y);
		adj[y].push_back(x);
	}

	bfs(0, d1);
	bfs(1, d2);
	bfs(n-1, d3);

	ll best = d1[n-1]*b + d2[n-1]*e;

	for(int i=0; i<n; ++i)
		best = std::min(best,
				d1[i]*b + d2[i]*e + d3[i]*p);

	std::cout << best << '\n';
}
