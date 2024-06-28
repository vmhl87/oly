// Investigation  -  https://cses.fi/problemset/task/1202/
//
// This problem is basically dijkstra spam lmao
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

	std::priority_queue<std::array<long long, 3>> pq; pq.push({0, 0, -1});
	long long dist[n] = {}, mult[n];
	int min[n], max[n];
	bool vis[n] = {};

	constexpr int M = 1e9 + 7;

	for(int i=0; i<n; ++i) mult[i] = 1, min[i] = n, max[i] = 0;
	min[0] = 0, max[0] = 0;

	while(pq.size()){
		std::array<long long, 3> top = pq.top(); pq.pop();

		if(!dist[top[1]]){
			dist[top[1]] = top[0];
			if(top[2]+1){
				mult[top[1]] = mult[top[2]];
				min[top[1]] = std::min(min[top[1]], min[top[2]] + 1);
				max[top[1]] = std::max(max[top[1]], max[top[2]] + 1);
			}

			for(const auto &[next, cost] : adj[top[1]]) if(!dist[next]){
				pq.push({top[0] - cost, next, top[1]});
			}
		}else if(dist[top[1]] == top[0] && top[2]+1){
			mult[top[1]] = (mult[top[1]] + mult[top[2]]) % M;
			min[top[1]] = std::min(min[top[1]], min[top[2]] + 1);
			max[top[1]] = std::max(max[top[1]], max[top[2]] + 1);
		}
	}

	std::cout << -dist[n-1] << ' ' << mult[n-1] << ' ' << min[n-1] << ' ' << max[n-1] << '\n';
}
