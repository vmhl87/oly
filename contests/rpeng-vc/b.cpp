#include <iostream>

int x[500], y[500];

int dist(int a, int b){
	return std::abs(x[a]-x[b]) + std::abs(y[a]-y[b]);
}

int dp[1000][1000];
bool s[1000][1000];

int best(int n, int k){
	if(n == 0) return 0;

	if(s[n][k]) return dp[n][k];
	s[n][k] = 1;

	int res = 1e9;

	for(int i=1; i<=k+1; ++i) if(n-i >= 0)
		res = std::min(res,
				dist(n, n-i) + best(n-i, k-i+1)
			);

	return dp[n][k] = res;
}

int main(){
	freopen("marathon.in", "r", stdin);
	freopen("marathon.out", "w", stdout);
	
	int n, k; std::cin >> n >> k;

	for(int i=0; i<n; ++i)
		std::cin >> x[i] >> y[i];

	std::cout << best(n-1, k) << '\n';
}
