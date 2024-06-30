#include <algorithm>
#include <iostream>
#include <vector>
#include <array>
#include <cmath>

typedef long long LL;

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int n, m; std::cin >> n >> m;

	int a[n], b[n];
	for(int i=0; i<n; ++i) std::cin >> a[i];
	for(int i=0; i<n; ++i) std::cin >> b[i];

	std::array<int, 2> d[n];
	for(int i=0; i<n; ++i) d[i][0] = a[i] - b[i], d[i][1] = a[i];

	std::sort(d, d+n);

	// remove tools that have obvious replacements
	std::vector<std::array<int, 2>> optimal;

	for(const auto &[delta, cap] : d)
		if(!optimal.size() || (delta > optimal.back()[0] && cap < optimal.back()[1]))
			optimal.push_back({delta, cap});

	int dp[optimal[0][1] + 1], p = optimal.size() - 1;

	for(int i=0; i<=optimal[0][1]; ++i){
		// delta = optimal[p][1], necessary = optimal[p][0];
		// check if we can go to next tool
		while(p && i >= optimal[p-1][1]) --p;

		if(i < optimal.back()[1]) dp[i] = 0;
		else dp[i] = dp[i - optimal[p][0]] + 1;
	}

	LL res = 0;

	for(int i=0; i<m; ++i){
		int v; std::cin >> v;

		if(v > optimal[0][1]){
			LL amt = 1 + (v - optimal[0][1])/optimal[0][0];

			v -= amt * optimal[0][0];
			res += amt;
		}

		res += dp[v];
	}

	std::cout << res*2 << '\n';
}
