#include <iostream>
#include <vector>
#include <array>
#include <queue>

using ll = long long;

std::vector<std::array<int, 3>> adj[200000];
bool vis[200000], use[200000];
int active[200000];
ll depth[200000];

int main(){
	int n, m; std::cin >> n >> m;

	for(int i=0; i<m; ++i){
		int a, b, c; std::cin >> a >> b >> c, --a, --b;
		adj[a].push_back({b, c, i});
		adj[b].push_back({a, c, i});
	}

	std::priority_queue<std::array<ll, 2>> d;
	d.push({0, 0});

	while(d.size()){
		ll cost = d.top()[0],
		   i = d.top()[1];
		d.pop();
		if(vis[i]) continue;
		vis[i] = 1;
		depth[i] = -cost;
		for(const auto &[n, c, j] : adj[i])
			if(!vis[n]) d.push({cost-c, n});
	}

	if(!vis[n-1]){
		for(int i=0; i<m; ++i) std::cout << "No\n";
		exit(0);
	}

	d.push({depth[n-1], n-1});
	int now = 1; active[n-1] = 1;

	while(d.size()){
		ll p = d.top()[0],
		   i = d.top()[1];
		d.pop();
		--now;
		if(--active[i]) continue;
		for(const auto &[n, c, j] : adj[i])
			if(depth[n] + c == depth[i]) ++now;
		for(const auto &[n, c, j] : adj[i])
			if(depth[n] + c == depth[i]){
				if(now==1) use[j] = 1;
				d.push({depth[n], n});
				++active[n];
			}
	}

	for(int i=0; i<m; ++i) std::cout << (use[i] ? "Yes\n" : "No\n");
}
