#include <iostream>
#include <vector>
#include <array>
#include <queue>

using ll = long long;

std::vector<std::array<int, 2>> adj[2500];

int ct[2500], par[2500];
bool vis[2500], s[2500];
ll depth[2500];

std::queue<int> q;

int main(){
	int n, m; std::cin >> n >> m;
	while(m--){
		int a, b, c; std::cin >> a >> b >> c;
		adj[a-1].push_back({b-1, c});
	}

	for(int i=0; i<n; ++i) q.push(i), vis[i] = 1;

	while(q.size()){
		int t = q.front(); q.pop(), vis[t] = 0;

		for(const auto &[x, w] : adj[t])
			if(depth[t] + w < depth[x]){
				depth[x] = depth[t] + w;
				par[x] = t;
				if(!vis[x]) q.push(x), vis[x] = 1;
				if(++ct[x] == n){
					int v = par[x];
					std::cout << "YES\n";
					std::vector<int> order;
					order.push_back(v);
					while(!s[v]){
						s[v] = 1, v = par[v];
						order.push_back(v);
					}
					while(s[order.back()]){
						std::cout << order.back()+1 << ' ';
						s[order.back()] = 0, order.pop_back();
					}
					std::cout << order.back()+1 << '\n';
					return 0;
				}
			}
	}

	std::cout << "NO\n";
}
