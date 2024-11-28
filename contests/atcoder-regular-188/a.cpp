#include <iostream>
#include <cstring>
#include <array>

using ll = long long;
const int m = 998244353;

char a[50];
int n, k;

int dp[55][55][55][55][8];

ll build(int t, std::array<int, 4> d){
	std::array<int, 4> c = {d[0], d[1], d[2], d[3]};

	if(dp[c[0]][c[1]][c[2]][c[3]][t] > -1)
		return dp[c[0]][c[1]][c[2]][c[3]][t];

	int i = -1;
	for(int j=0; j<4; ++j) i += c[j];

	if(i == n){
		int res = 0;
		for(int i=0; i<4; ++i)
			res += (c[i]*(c[i]-1))/2;
		return dp[c[0]][c[1]][c[2]][c[3]][t] = res>=k;
		return res >= k;
	}else{
		ll res = 0;
		for(int j=0; j<3; ++j)
			if(a[i] == 'A'+j || a[i] == '?'){
				t ^= 1<<j;
				++c[t<4?t:t^7];
				res = (res + build(t, c)) % m;
				--c[t<4?t:t^7];
				t ^= 1<<j;
			}
		return dp[c[0]][c[1]][c[2]][c[3]][t] = res;
	}
}

int main(){
	std::cin >> n >> k;
	for(int i=0; i<n; ++i) std::cin >> a[i];

	memset(dp, -1, sizeof dp);

	std::cout << build(0, {1, 0, 0, 0}) << '\n';
}
