// Dominos Tiling  -  https://dmoj.ca/problem/dwite10c3p3
// Pretty simple by matrix multiplication
// bin exp unnecessary due to constraint

#include <iostream>

using LL = long long;

// extend for higher max n
LL dp[31][12];

const LL M = 1000000;

// 0: vvv
// 1: vv^
// 2: v^v
// 3: v^^
// 4: ^vv
// 5: ^v^
// 6: ^^v
// 7: ^^^
// 8: <>v
// 9: v<>
// 10: <>^
// 11: ^<>

// would be even faster with mat expo
const int t[12][12] = {
	{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
	{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
};

void test_case(){
	int n; std::cin >> n;

	// initial valid cases
	for(int i=0; i<12; ++i) dp[1][i] = 0;
	dp[1][0] = 1, dp[1][8] = 1, dp[1][9] = 1;

	for(int i=2; i<=n; ++i){
		for(int j=0; j<12; ++j) dp[i][j] = 0;

		// transformation mat
		for(int j=0; j<12; ++j)
			for(int k=0; k<12; ++k)
				dp[i][k] += dp[i-1][j] * t[j][k];

		for(int j=0; j<12; ++j) dp[i][j] %= M;
	}

	std::cout << (dp[n][7] + dp[n][10] + dp[n][11]) % M << '\n';
}

int main(){
	for(int i=0; i<5; ++i) test_case();
}
