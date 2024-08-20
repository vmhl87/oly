#include <iostream>

using ll = long long;

int p;

ll dp[501][501][2];
bool done[501][501][2];

// an attempt at the stupid bruteforce solution.
// observation made here was to model the paths as
// "propagating" some set of k weights down the tree,
// and leaving them behind at some places. to mantain
// deterministic all that was necessary was to ensure
// branches didn't get equal amount.

ll comp(int n, int k, int stable){
	if(n == 1) return 1;
	if(k == 0) return 1;
	if(done[n][k][stable]) return dp[n][k][stable];
	ll sum = 0;
	for(int i=0; i<=k; ++i)
		for(int j=0; i+j<=k; ++j)
			if(!stable || i != j){
				//std::cout << n << ',' << k << " -> " << i << ',' << j << '\n';
				sum = (sum + (
							comp(n-1, i, stable&&i>j)*
							comp(n-1, j, stable&&j>i)
						% p)) % p;
			}
	dp[n][k][stable] = sum;
	done[n][k][stable] = 1;
	return sum;
}

void test_case(){
	int n, k; std::cin >> n >> k >> p;
	std::cout << comp(n, k, 1) << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test_case();
}
