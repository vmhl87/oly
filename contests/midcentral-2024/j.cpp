#include <iostream>

int a[1005][1005];

int main(){
	int n, k; std::cin >> n >> k;

	int res = 0;

	for(int i=0; i<=n; ++i){
		a[i][0] = 1 % k;
		for(int j=1; j<=i; ++j)
			a[i][j] = (a[i-1][j-1] + a[i-1][j]) % k;

		for(int j=0; j<=i; ++j) if(a[i][j] == 0)
			++res;
	}

	std::cout << res << '\n';
}
