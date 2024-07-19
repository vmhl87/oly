#include <iostream>
#include <vector>

using LL = long long;

int n, cost[200000], y[200000];
std::vector<int> adj[200000];
LL dp[200000][4];  // 0: lit, needs external
				   // 1: lit, sufficient
				   // 2: unlit, needs
				   // 3: unlit, sufficient

const int BIG = 200000000;

void dfs(int i, int p){
	for(int x : adj[i]) if(x != p) dfs(x, i);

	dp[i][0] += cost[i], dp[i][1] += cost[i];

	if(y[i]){
		// if lit, can choose any state of child
		for(int x : adj[i]) if(x != p)
			dp[i][0] += std::min(std::min(dp[x][0], dp[x][1]),
								 std::min(dp[x][2], dp[x][3]));
		dp[i][1] = dp[i][0];

		// if not lit, can only choose 'sufficient' of child
		for(int x : adj[i]) if(x != p)
			dp[i][2] += std::min(dp[x][1], dp[x][3]);
		dp[i][3] = dp[i][2];
	}else{
		// if no children, cannot be sufficient
		if(adj[i].size() - (p == -1 ? 0 : 1) == 0)
			dp[i][1] = BIG, dp[i][3] = BIG;

		// if lit, needs external: can choose any
		// state of child BESIDES lit+sufficient
		for(int x : adj[i]) if(x != p)
			dp[i][0] += std::min(std::min(dp[x][2], dp[x][3]),
								 dp[x][0]);

		// if lit+sufficient: must be lit by child
		// which is also sufficient - choose 1
		int opt = 0;
		LL delta = 0;
		for(int x : adj[i]) if(x != p){
			LL curr = std::min(std::min(dp[x][0], dp[x][1]),
							   std::min(dp[x][2], dp[x][3]));
			dp[i][1] += curr;
			if(dp[x][1] == curr) opt = 1;
			else{
				LL next = dp[x][1] - curr;
				if(delta == 0 || next < delta) delta = next;
			}
		}
		if(!opt) dp[i][1] += delta;

		// if not lit and needs lit: firstly all children must
		// be sufficient, secondly no child can light
		for(int x : adj[i]) if(x != p)
			dp[i][2] += dp[x][3];

		// if not lit and sufficient: all children must be suff
		// and one child must light
		opt = 0, delta = 0;
		for(int x : adj[i]) if(x != p){
			LL curr = std::min(dp[x][1], dp[x][3]);
			dp[i][3] += curr;
			if(dp[x][1] == curr) opt = 1;
			else{
				LL next = dp[x][1] - curr;
				if(delta == 0 || next < delta) delta = next;
			}
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
