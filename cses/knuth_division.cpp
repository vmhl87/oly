#include <iostream>

using ll = long long;
const int N = 5e3;

ll a[N+2], b[N][N];
int c[N][N];

ll f(int i, int j, int k){
	return a[j+i+1] - a[j] + b[j][k] + b[k+1][j+i];
}

int main(){
	int n; std::cin >> n;
	for(int i=0, j; i<n; ++i) std::cin >> j, a[i+1] = a[i] + j;

	for(int i=0; i<n; ++i){
		for(int j=0; j<n; ++j)
			b[i][j] = 1e18;
		b[i][i] = 0, c[i][i] = i;
	}

	for(int i=1; i<n; ++i)
		for(int j=0; j<n-i; ++j)
			for(int k=c[j][i+j-1]; k<j+i && k<=c[j+1][i+j]; ++k){
				ll r = a[j+i+1] - a[j] + b[j][k] + b[k+1][j+i];
				if(r < b[j][j+i]) b[j][j+i] = r, c[j][j+i] = k;
			}

	std::cout << b[0][n-1] << '\n';
}
