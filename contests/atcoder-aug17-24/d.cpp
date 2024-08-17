#include <iostream>

using LL = long long;

int a[200000], p[200001], c[1000000];

int main(){
	int n, m; std::cin >> n >> m;
	for(int i=0; i<n; ++i) std::cin >> a[i];

	for(int i=0; i<n; ++i){
		p[i+1] = (p[i]+a[i])%m;
		++c[p[i+1]];
	}

	//if(p[n] != 0) ++c[0];

	LL ans = 0;

	for(int i=0; i<m; ++i){
		ans += ((LL)c[i]*((LL)c[i]-1LL))/2;
		c[i] = 0;
	}

	for(int i=1; i<=n; ++i){
		ans += c[(p[i]+m-p[n])%m];
		++c[p[i]];
	}

	std::cout << ans << '\n';
}
