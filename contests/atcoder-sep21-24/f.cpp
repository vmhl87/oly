#include <iostream>
#include <array>
#include <set>
#include <map>

using ll = long long;

const ll m = 998244353;

std::map<int, int> jmp;
std::set<int> jpos;
int n;

std::map<int, std::array<ll, 200001>> dp;

ll count(int i, int k){
	if(k<=0) return 1;

	if(!dp[i][k]){
		ll res = 0;

		if(jpos.count(i)) res += count(jmp[i], k-1);

		auto iter = jpos.upper_bound(i);
		if(iter == jpos.end()) iter = jpos.begin(), i -= n;
		res += count(*iter, k-((*iter)-i));

		dp[i][k] = res % m;
	}

	return dp[i][k];
}

int main(){
	int m, k; std::cin >> n >> m >> k;

	for(int i=0; i<m; ++i){
		int x, y; std::cin >> x >> y;
		jpos.insert(x-1);
		jmp[x-1] = y-1;
	}

	if(m == 0) std::cout << 1 << '\n', exit(0);

	std::cout << count(0, k) << '\n';
}
