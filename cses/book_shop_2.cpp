#include <iostream>

const int maxn = 1e5;

int dp[maxn+1], alt[maxn+1], h[100], s[100], k[100];

int main(){
	int n, x; std::cin >> n >> x;

	for(int i=0; i<n; ++i) std::cin >> h[i];
	for(int i=0; i<n; ++i) std::cin >> s[i];
	for(int i=0; i<n; ++i) std::cin >> k[i];

	for(int i=0; i<n; ++i){
		for(int j=0; j<=x; ++j) alt[j] = dp[j];

		for(int j=0; j<h[i]; ++j){
			for(int r=j; r<=x; r+=h[i]){
			}
		}

		for(int j=0; j<=x; ++j) dp[j] = alt[j];
	}

	std::cout << dp[x] << '\n';
}
