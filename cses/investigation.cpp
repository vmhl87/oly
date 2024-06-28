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

	std::priority_queue<std::array<long long, 2>> pq; pq.push({0, 0});
	int mult[n], min[n], max[n];
	long long dist[n] = {};
	bool vis[n] = {};

	constexpr int M = 1e9 + 7;

	for(int i=0; i<n; ++i) mult[i] = 1, min[i] = n, max[i] = 0;
	min[0] = 0, max[0] = 0;

	while(pq.size()){
		std::array<long long, 2> top = pq.top(); pq.pop();

		for(const auto &[next, cost] : adj[top[1]]) if(!vis[next]){
			pq.push({top[0] - cost, next});

			dist[next] = cost - top[0];
			mult[next] = mult[top[1]];

			min[next] = std::min(min[next], min[top[1]] + 1);
			max[next] = std::max(max[next], max[top[1]] + 1);

			vis[next] = 1;
		}else if(cost - top[0] == dist[next]){
			mult[next] = (mult[next] + mult[top[1]]) % M;

			min[next] = std::min(min[next], min[top[1]] + 1);
			max[next] = std::max(max[next], max[top[1]] + 1);
		}
	}

	std::cout << dist[n-1] << ' ' << mult[n-1] << ' ' << min[n-1] << ' ' << max[n-1] << '\n';
}
