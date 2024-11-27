#include <iostream>

using ll = long long;
constexpr int N = 1e9 + 7;

ll dp[1<<19][19];
int adj[20][20];

bool cmp(int a, int b){
	return __builtin_popcount(a) < __builtin_popcount(b);
}

int main(){
	int n, m; std::cin >> n >> m;
	
	while(m--){
		int a, b; std::cin >> a >> b;
		++adj[a-1][b-1];
	}

	dp[0][0] = 1;

	for(int j=0; j<1<<(n-1); ++j){
		for(int k=0; k<n-1; ++k) if(!(j&(1<<k))){
			if(j == 0 && k == 0) continue;
			for(int x=0; x<n-1; ++x) if(j&(1<<x))
				dp[j][k] += adj[x][k] * dp[j^(1<<x)][x];
			dp[j][k] %= N;
		}
	}

	ll res = 0, all = (1<<(n-1))-1;
	for(int j=0; j<n-1; ++j)
		res += adj[j][n-1] * dp[all^(1<<j)][j];

	std::cout << res % N << '\n';
}
