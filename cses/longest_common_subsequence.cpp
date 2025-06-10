#include <iostream>
#include <array>

std::array<int, 3> dp[1001][1001];
int c[1000], d[1000];

int main(){
	int a, b; std::cin >> a >> b;
	for(int i=0; i<a; ++i) std::cin >> c[i];
	for(int i=0; i<b; ++i) std::cin >> d[i];

	for(int i=a-1; i>=0; --i)
		for(int j=b-1; j>=0; --j)
			dp[i][j] = std::max((std::array<int, 3>){dp[i+1][j+1][0] + (c[i] == d[j]), 1, 1},
					std::max((std::array<int, 3>){dp[i+1][j][0], 1, 0}, {dp[i][j+1][0], 0, 1}));

	std::cout << dp[0][0][0] << '\n';

	int i=0, j=0;

	while(i < a && j < b){
		if(c[i] == d[j]) std::cout << c[i] << ' ';
		auto dir = dp[i][j];
		i += dir[1], j += dir[2];
	}

	std::cout << '\n';
}
