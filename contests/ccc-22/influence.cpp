#include <iostream>
#include <vector>

using LL = long long;

int n, cost[200000], y[200000];
std::vector<int> adj[200000];
LL dp[200000][4];  // need+nolight, don't+nolight, need+light, don't+light

const int BIG = 2000000000;

void dfs(int i, int p){
	for(int x : adj[i]) if(x != p) dfs(x, i);

	if(y[i]){
		// if don't light, can only pick child that doesn't need
		for(int x : adj[i]) if(x != p){
			dp[i][0] += std::min(dp[x][1], dp[x][3]);
			dp[i][1] += std::min(dp[x][1], dp[x][3]);
		}

		dp[i][2] += cost[i], dp[i][3] += cost[i];

		// if does light can pick all
		for(int x : adj[i]) if(x != p){
			dp[i][2] += std::min(std::min(dp[x][1], dp[x][3]),
								 std::min(dp[x][0], dp[x][2]));
			dp[i][3] += std::min(std::min(dp[x][1], dp[x][3]),
								 std::min(dp[x][0], dp[x][2]));
		}
	}else{
		if(adj[i].size() - (p == -1 ? 0 : 1) == 0)
			dp[i][1] = BIG, dp[i][3] = BIG;
		
		// if need and don't light, only valid child is don't need and no light
		for(int x : adj[i]) if(x != p) dp[i][0] += dp[x][1];

		// if don't need but no light, child must not need, have a light
		int opt = 0;
		LL delta = 0;
		for(int x : adj[i]) if(x != p){
			// pick from any
			// check if opt
			if(dp[x][3] <= dp[x][1]) opt = 1;
			else{
				LL next = dp[x][3] - dp[x][1];
				if(delta == 0 || next < delta) delta = next;
			}
			dp[i][1] += std::min(dp[x][1], dp[x][3]);
		}
		if(!opt) dp[i][1] += delta;

		dp[i][2] += cost[i], dp[i][3] += cost[i];

		// if need and light, no child must light, children can need/not
		for(int x : adj[i]) if(x != p) dp[i][2] += std::min(dp[x][0], dp[x][1]);

		// if don't need and light, can pick any, must have a light
		opt = 0;
		delta = 0;
		for(int x : adj[i]) if(x != p){
			// pick from any
			// check if opt
			if(std::min(dp[x][2], dp[x][3]) <= std::min(dp[x][0], dp[x][1])) opt = 1;
			else{
				LL next = std::min(dp[x][2], dp[x][3]) - std::min(dp[x][0], dp[x][1]);
				if(delta == 0 || next < delta) delta = next;
			}
			dp[i][3] += std::min(std::min(dp[x][0], dp[x][1]),
								 std::min(dp[x][2], dp[x][3]));
		}
		if(!opt) dp[i][3] += delta;
	}
}

int main(){
	std::cin >> n;

	for(int i=1; i<n; ++i){
		int a, b; std::cin >> a >> b, --a, --b;
		adj[a].push_back(b), adj[b].push_back(a);
	}

	for(int i=0; i<n; ++i){
		char c; std::cin >> c;
		y[i] = c=='Y';
	}

	for(int i=0; i<n; ++i) std::cin >> cost[i];

	dfs(0, -1);

	for(int i=0; i<n; ++i) std::cout << (i+1)%10 << " \n"[i==n-1];
	for(int i=0; i<4; ++i)
		for(int j=0; j<n; ++j){
			if(dp[j][i] >= BIG) std::cout << '-';
			else std::cout << dp[j][i];
			std::cout << " \n"[j==n-1];
		}

	std::cout << std::min(dp[0][1], dp[0][3]) << '\n';
}
