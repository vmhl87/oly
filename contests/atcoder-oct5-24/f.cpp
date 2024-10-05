#include <iostream>
#include <map>

using ll = long long;

int n, k, x;
ll t[100];

std::map<ll, ll> dp[100];

ll best(int i, ll start){
	if(i >= n) return 0;

	if(dp[i].count(start)) return dp[i][start];

	ll res = -1;

	// lump anywhere from 1 to k orders
	for(int j=1; j<=k; ++j){
		if(i+j-1 >= n) break;
		ll s = std::max(start, t[i+j-1]);
		ll comp = best(i+j, s+x);
		for(int e=0; e<j; ++e)
			comp += s-t[i+e];
		if(res==-1 || comp<res) res = comp;
	}

	if(res == -1) res = 0;

	dp[i][start] = res;
	return res;
}

int main(){
	std::cin >> n >> k >> x;
	for(int i=0; i<n; ++i) std::cin >> t[i];

	std::cout << best(0, 0) << '\n';
}
