#include <iostream>

using ll = long long;

int x[3000];

ll dp[3000][3000];

ll best(int k, int r){
	if(k == 0) return r == 0 ? 0 : 1e18;
	if(dp[k][r]) return dp[k][r] - 1;

	ll res = 1e18, acc = 0;

	for(int i=r; i+1; --i){
		res = std::min(res, best(k-1, i) + acc*acc);
		acc += x[i-1];
	}

	dp[k][r] = res + 1;
	return res;
}

int main(){
	int n, k; std::cin >> n >> k;
	for(int i=0; i<n; ++i) std::cin >> x[i];

	std::cout << best(k, n) << '\n';
}
