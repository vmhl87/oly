#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <array>
#include <queue>
 
using ll = long long;
const int maxn = 1e5;
 
std::vector<std::array<int, 2>> adj[maxn], bdj[maxn];;
bool vis[maxn], vis2[maxn];
ll dep[maxn], rem[maxn];
 
int main(){
	int n, m; std::cin >> n >> m;
	while(m--){
		int a, b, c; std::cin >> a >> b >> c;
		adj[--a].push_back({--b, c});
		bdj[b].push_back({a, c});
	}
 
	std::priority_queue<std::array<ll, 2>> djk;
	djk.push({0, 0});
 
	while(djk.size()){
		ll r = djk.top()[0], t = djk.top()[1]; djk.pop();

		if(vis[t]) continue;
		vis[t] = 1;
		
		for(const auto &[x, c] : adj[t]) if(!vis[x])
			djk.push({r-c, x}), dep[x] = dep[t]+c;
	}
 
	djk.push({dep[n-1], n-1});
	std::vector<int> res;
	int over = 1; rem[n-1] = 1;
 
	while(djk.size()){
		ll r = djk.top()[0], t = djk.top()[1]; djk.pop();

		//if(vis2[t]) continue;
		//vis2[t] = 1;
 
		//if(!(over -= rem[t])) res.push_back(t+1);

		--over;
		if(--rem[t]) continue;
		if(!over) res.push_back(t+1);
 
		for(const auto &[x, c] : bdj[t]) if(vis[x] && !vis2[x] && dep[x] == dep[t]-c)
			djk.push({r-c, x}), ++rem[x], ++over;
	}
 
	std::cout << res.size() << '\n';
	std::sort(res.begin(), res.end());
	for(int x : res) std::cout << x << ' ';
	std::cout << '\n';
}
