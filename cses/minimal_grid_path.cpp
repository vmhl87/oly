#include <iostream>
#include <cassert>

const int N = 3e3;

char a[N][N], b[N+N-1];
bool o[N][N];

int main(){
	int n; std::cin >> n;

	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j)
			std::cin >> a[i][j];

	o[0][0] = 1, b[0] = a[0][0];

	for(int i=1; i<n+n-1; ++i){
		char best = 'Z'+1;

#define c(x, y) if(x < n && y < n && a[x][y] < best) best = a[x][y];
		for(int j=0; j<i; ++j){
			int k = i-j-1;
			if(k < n && o[j][k]){
				c(j+1, k)
				c(j, k+1)
			}
		}
#undef c

#define c(x, y) if(x < n && y < n && a[x][y] == best) o[x][y] = 1;
		for(int j=0; j<i; ++j){
			int k = i-j-1;
			if(k < n && o[j][k]){
				c(j+1, k)
				c(j, k+1)
			}
		}
#undef c
	}

	assert(o[n-1][n-1] == 1);

	for(int i=n-1, j=n-1; i || j;){
		b[i+j] = a[i][j];
		if(i && o[i-1][j]) --i;
		else --j;
	}

	for(int i=0; i<n+n-1; ++i) std::cout << b[i];
	std::cout << '\n';
}
