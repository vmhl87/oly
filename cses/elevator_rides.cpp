#include <iostream>
#include <array>

std::array<int, 2> dp[1<<20];
int a[20];

int main(){
	int n, x; std::cin >> n >> x;
	for(int i=0; i<n; ++i) std::cin >> a[i];

	dp[0] = {1, 0};

	for(int i=1; i<1<<n; ++i){
		dp[i] = {n+1, 0};

		for(int j=0; j<n; ++j) if(i&(1<<j)){
			std::array<int, 2> t = dp[i^(1<<j)];
			if(t[1]+a[j] > x) ++t[0],
				t[1] = std::min(t[1], a[j]);
			else t[1] += a[j];
			dp[i] = std::min(dp[i], t);
		}
	}

	std::cout << dp[(1<<n)-1][0] << '\n';
}
