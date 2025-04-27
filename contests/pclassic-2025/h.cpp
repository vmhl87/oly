#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <map>
#include <set>

const int N = 1e5;

std::vector<std::array<int, 2>> adj[N*4];
int nxt;

std::map<int, int> m[N];

int x, y;

void edge(int a, int b, int c){
	adj[a].push_back({b, c});
	adj[b].push_back({a, c});
}

void addto(int a, int b, int c){
	edge(a, b, x);
	
	if(!m[a][c]) m[a][c] = nxt++;
	else edge(m[a][c], b, 0);
}

using ll = long long;
ll dist[N*4];

int main(){
	int n, m, c, s, t;
	std::cin >> n >> m >> c >> x >> y >> s >> t, --s, --t;
	nxt = n;

	while(m--){
		int u, v, z; std::cin >> u >> v >> z, --u, --v;
		int r = nxt++;
		addto(u, r, z);
		addto(v, r, z);
	}

	/*
	for(int i=0; i<nxt; ++i){
		for(const auto &[j, C] : adj[i]) if(j > i) std::cout << i << " <-> " << j << " (cost " << C << ")\n";
	}
	*/

	std::priority_queue<std::array<ll, 2>> q; q.push({-1, s});

	while(q.size()){
		int z = q.top()[1], Y = -q.top()[0]; q.pop();

		if(dist[z]) continue;
		dist[z] = Y;

		if(z == t) break;

		for(const auto &[x, C] : adj[z]) if(!dist[x]){
			ll r = dist[z] + C;
			if(z >= n) r += y*2;
			q.push({-r, x});
		}
	}

	if(dist[t] == 0) std::cout << -1 << '\n';
	else std::cout << (dist[t]/2) - x << '\n';
}
