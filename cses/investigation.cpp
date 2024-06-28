// Investigation  -  https://cses.fi/problemset/task/1202/
//
// This problem is basically dijkstra spam lmao
//
// To find the lowest cost path we do standard dijkstra
// however we are interested not only in the best path but how many -
// we therefore do a node-counting style approach, marking each node with
// the number of minimum cost patsh to it, and generating each next node
// from the sum of the counts of all of the nodes which have minimum cost
// paths leading toward it: essentially dp
//
// min/max flights is done very similarly

#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <array>

int main(){
	int n, m; std::cin >> n >> m;

	std::vector<std::array<long long, 2>> adj[n];

	while(m--){
		int a, b, c; std::cin >> a >> b >> c;

		adj[a-1].push_back({b-1, c});
	}

	// using negative cost as first argument for easy usage
	// 2nd & 3rd elements are current node and parent node
	std::priority_queue<std::array<long long, 3>> pq; pq.push({0, 0, -1});
	// distance, count
	long long dist[n] = {}, mult[n];
	int min[n], max[n];
	bool vis[n] = {};

	constexpr int M = 1e9 + 7;

	for(int i=0; i<n; ++i) mult[i] = 1, min[i] = n, max[i] = 0;
	min[0] = 0, max[0] = 0;

	while(pq.size()){
		std::array<long long, 3> top = pq.top(); pq.pop();

		// if not marked, this is first time reaching said node, and must be
		// the lowest cost path - initialize everything
		if(!dist[top[1]]){
			dist[top[1]] = top[0];

			// if node has a parent update its counts/min/max
			if(top[2]+1){
				mult[top[1]] = mult[top[2]];
				min[top[1]] = std::min(min[top[1]], min[top[2]] + 1);
				max[top[1]] = std::max(max[top[1]], max[top[2]] + 1);
			}

			// only push connections on first time reached
			for(const auto &[next, cost] : adj[top[1]]) if(!dist[next]){
				pq.push({top[0] - cost, next, top[1]});
			}

		// otherwise check if this path meets the optimal cost to node
		// and if so update counts/min/max
		}else if(dist[top[1]] == top[0] && top[2]+1){
			mult[top[1]] = (mult[top[1]] + mult[top[2]]) % M;
			min[top[1]] = std::min(min[top[1]], min[top[2]] + 1);
			max[top[1]] = std::max(max[top[1]], max[top[2]] + 1);
		}
	}

	std::cout << -dist[n-1] << ' ' << mult[n-1] << ' ' << min[n-1] << ' ' << max[n-1] << '\n';
}
