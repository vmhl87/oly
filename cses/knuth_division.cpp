#include <iostream>

using ll = long long;
const int N = 5e3;

ll a[N+2], b[N][N+1];

ll f(int i, int j, int k){
	return a[j+i+1] - a[j] + b[j][k] + b[k+1][j+i];
}

int main(){
	int n; std::cin >> n;
	for(int i=0, j; i<n; ++i) std::cin >> j, a[i+1] = a[i] + j;
	a[n+1] = 1e18;

	for(int i=0; i<n; ++i){
		for(int j=0; j<=n; ++j)
			b[i][j] = 1e18;
		b[i][i] = 0;
	}

	for(int i=1; i<n; ++i)
		for(int j=0; j<n-i; ++j){
			//for(int k=j; k<=j+i; ++k)
				//b[j][j+i] = std::min(b[j][j+i],
					//a[j+i+1] - a[j] + b[j][k] + b[k+1][j+i]);
			int k=j;
			for(k=j; k<j+i; ++k)
				if(f(i, j, k) < f(i, j, k+1))
					break;
			//for(int s=1<<13; s; s/=2)
				//if(k+s < j+i && f(i, j, k+s-1) >= f(i, j, k+s))
					//k += s;
			b[j][j+i] = f(i, j, k);
		}

	std::cout << b[0][n-1] << '\n';
}
