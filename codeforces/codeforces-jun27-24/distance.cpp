#include <iostream>

const int m = 998244353;

int main(){
	int n, k; std::cin >> n >> k;

	long long dp1[n+1][k+1], dp11[n+1][k+1], dp2[n+1][k+1], dp22[n+1][k+1];

	for(int i=0; i<=n; ++i) for(int j=0; j<=k; ++j) dp1[i][j] = 0, dp11[i][j] = 0, dp2[i][j] = 0, dp22[i][j] = 0;

	dp1[1][1] = 1;
	dp2[1][0] = 1;

	for(int i=2; i<=n; ++i){
		for(int j=0; j<=k; ++j){
			dp2[i][j] += dp11[i-1][j] + dp2[i-1][j];

			if(j){
				dp1[i][j] += dp2[i-1][j-1];
				dp11[i][j] += dp1[i-1][j-1] + dp11[i-1][j-1];
			}

			if(j == k){
				dp1[i][j] += dp2[i-1][j];
				dp11[i][j] += dp1[i-1][j] + dp11[i-1][j];
			}

			dp1[i][j] %= m;
			dp11[i][j] %= m;
			dp2[i][j] %= m;
			dp22[i][j] %= m;
		}
	}

	long long res = (dp11[n][k] + dp2[n][k] + dp22[n][k]) % m;

	std::cout << res << '\n';
}
