#include <iostream>
#include <bitset>
#include <string>

std::bitset<1<<18> dp;

void test(){
	int n; std::cin >> n;
	std::string s; std::cin >> s;

	dp.reset();
	
	dp[(1<<n)-1] = s[(1<<n)-2] == '0';

	for(int i=(1<<n)-2; i>=0; --i){
		if(i > 0 && s[i-1] == '1') continue;

		bool w = 0;

		for(int x=0; x<n; ++x) // if(!(i&(1<<x)))
			if(dp[i|(1<<x)]) { w = 1; break; }

		dp[i] = w;
	}

	std::cout << (dp[0] ? "Yes" : "No") << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
