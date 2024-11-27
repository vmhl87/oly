#include <iostream>
#include <string>

using ll = long long;
const int m = 1e9 + 7;

std::string s, a[100000];
int n;

bool match(int i, int j){
	for(int x=0; x<a[j].length(); ++x)
		if(i+x >= s.length() || s[i+x] != a[j][x])
			return 0;
	return 1;
}

ll dp[5000];

ll way(int i){
	if(i == s.length()) return 1;

	if(dp[i]) return dp[i]-1;

	ll res = 0;

	for(int j=0; j<n; ++j)
		if(match(i, j))
			res = (res + way(i+a[j].length())) % m;

	dp[i] = res+1;
	return res;
}

int main(){
	std::cin >> s;
	std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> a[i];

	std::cout << way(0) << '\n';
}
