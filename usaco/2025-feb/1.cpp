#include <iostream>
#include <vector>
#include <array>

using ll = long long;
const int N = 2e5;

int a[N], c[N];

std::array<ll, 2> dp[N]; // 0: cost if unpicked, 1: cost if picked
std::vector<int> adj[N];
bool vis[N];

void dfs(int i){
	vis[i] = 1;

	for(int x : adj[i]) if(!vis[x]){
		dfs(x);
		dp[i][0] += std::max(dp[x][0], dp[x][1]);
		dp[i][1] += dp[x][0];
	}
}

int main(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> a[i], --a[i];
	for(int i=0; i<n; ++i) std::cin >> c[i];

	for(int i=0; i<n; ++i) if(i == a[i]) c[i] = 0;

	ll best = 0;

	for(int i=0; i<n; ++i) best += c[i];

	if(n <= 20){
		for(int i=0; i<1<<n; ++i){
			ll cost = 0;
			for(int j=0; j<n; ++j) if(i&(1<<j)) cost += c[j];
			bool work = 1;
			for(int j=0; j<n; ++j) if(!((i&(1<<j)) || (i&(1<<a[j]))))
				work = 0;
			if(work) best = std::min(best, cost);
		}

		std::cout << best << '\n';

	}else{
		for(int i=0; i<n; ++i) if(c[i] && c[a[i]])
			adj[i].push_back(a[i]), adj[a[i]].push_back(i);

		for(int i=0; i<n; ++i) dp[i][1] = c[i];

		ll rem = 0;

		for(int i=0; i<n; ++i) if(!vis[i])
			dfs(i), rem += std::max(dp[i][0], dp[i][1]);

		std::cout << best-rem << '\n';
	}
}
