#include <iostream>

using ll = long long;

int a[200000];

ll dp[200000][2];
bool fin[200000][2];

ll best(int i, int par){
	if(i==0){
		if(par) return 0;
		return a[0];
	}
	if(fin[i][par]) return dp[i][par];
	ll ans;
	if(par) ans = std::max(a[i]*2 + best(i-1, 0), best(i-1, 1));
	else ans = std::max(a[i] + best(i-1, 1), best(i-1, 0));
	fin[i][par] = 1;
	dp[i][par] = ans;
	return ans;
}

int main(){
	int n; std::cin >> n;
	for(int i=0; i!=n; ++i) std::cin >> a[i];

	std::cout << std::max(best(n-1, 0), best(n-1, 1)) << '\n';
}
