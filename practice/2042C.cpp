// URL: https://codeforces.com/contest/2042/problem/C

#include <iostream>
#include <bitset>

const int N = 2e5;

std::bitset<N> a;
int b[N+1];

void test(){
	int n, k; std::cin >> n >> k;

	for(int i=0; i<=n; ++i) b[i] = 0;

	for(int i=0; i<n; ++i){
		char c; std::cin >> c;
		a[i] = c == '1';
	}

	for(int i=n-1, x=0; i; --i){
		x += a[i]*2 - 1;
		if(x > 0) ++b[x];
	}

	for(int i=n, x=0, c=1; i; --i) if(b[i])
		for(int j=0; j<b[i]; ++j) if((++c, x += i) >= k){
			std::cout << c << '\n';
			return;
		}

	std::cout << -1 << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
