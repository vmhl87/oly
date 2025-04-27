#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <set>

const int N = 1e5;

std::vector<std::array<int, 2>> adj[N];

std::set<int> vis[N];
int dist[N];

std::vector<int> adj2[N*2];
int nxt;

void dfs(int i, int c, int a){
	vis[i].insert(c);

	if(c){
		adj2[i].push_back(a);
		adj2[a].push_back(i);
		for(const auto &[j, C] : adj[i]) if(C == c && !vis[j].count(c)){
			dfs(j, c, a);
		}
	}

	for(const auto &[j, C] : adj[i]) if(C != c && !vis[j].count(C)){
		int r = nxt++;
		//std::cout << r << " originates from " << i << " color " << C << '\n';
		vis[i].insert(C);
		adj2[i].push_back(r);
		adj2[r].push_back(i);
		dfs(j, C, r);
	}
}

int main(){
	int n, m, c, x, y, s, t;
	std::cin >> n >> m >> c >> x >> y >> s >> t, --s, --t;

	nxt = n;

	while(m--){
		int u, v, z; std::cin >> u >> v >> z, --u, --v;
		adj[u].push_back({v, z});
		adj[v].push_back({u, z});
	}

	for(int i=0; i<n; ++i) if(!vis[i].size()) dfs(i, 0, -1);

	/*
	for(int i=0; i<nxt; ++i){
		for(int j : adj2[i]) if(j > i) std::cout << i << " <-> " << j << '\n';
	}
	*/

	std::queue<int> q; q.push(s); dist[s] = 1;

	while(q.size()){
		int z = q.front(); q.pop();

		if(z == t) break;

		for(int x : adj2[z]) if(!dist[x]){
			dist[x] = dist[z] + 1;
			q.push(x);
		}
	}

	if(dist[t] == 0){
		std::cout << -1 << '\n';
		return 0;
	}

	long long d = dist[t];

	//std::cout << "pre: " << d << '\n';

	d /= 2;

	std::cout << x*(d-1) + y*d << '\n';
}
