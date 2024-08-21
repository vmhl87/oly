// First considered some sort of MST, but that isn't
// optimal for single point -> point. Instead used dijkstra
// to compute distance from start to every node, and from
// every node to end. Then, consider for every edge the
// cost of using the discount on that edge.

#include <iostream>
#include <vector>
#include <queue>
#include <array>

using ll = long long;

std::vector<std::array<int, 2>> adj[100000], bdj[100000];
std::array<int, 3> flights[200000];
bool vis[100000], vis2[100000];
ll start[100000], end[100000];

int main(){
	int n, m; std::cin >> n >> m;
	for(int i=0; i<m; ++i){
		int a, b, c; std::cin >> a >> b >> c, --a, --b;
		adj[a].push_back({b, c}), bdj[b].push_back({a, c});
		flights[i][0] = a, flights[i][1] = b, flights[i][2] = c;
	}

	std::priority_queue<std::array<ll, 2>> q;
	q.push({0, 0});

	while(q.size()){
		std::array<ll, 2> c = q.top(); q.pop();
		if(!vis[c[1]]){
			start[c[1]] = -c[0];
			vis[c[1]] = 1;
			for(const auto &[x, cost] : adj[c[1]]) if(!vis[x])
				q.push({c[0]-cost, x});
		}
	}

	q.push({0, n-1});

	while(q.size()){
		std::array<ll, 2> c = q.top(); q.pop();
		if(!vis2[c[1]]){
			end[c[1]] = -c[0];
			vis2[c[1]] = 1;
			for(const auto &[x, cost] : bdj[c[1]]) if(!vis2[x])
				q.push({c[0]-cost, x});
		}
	}

	ll best = 0;

	for(int i=0; i<m; ++i){
		if(vis[flights[i][0]] && vis2[flights[i][1]]){
			ll res = start[flights[i][0]] + end[flights[i][1]];
			res += flights[i][2]/2;
			if(res < best || best == 0) best = res;
		}
	}

	std::cout << best << '\n';
}
