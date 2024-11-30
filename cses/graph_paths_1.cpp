#include <iostream>
#include <array>

using ll = long long;
using mat = std::array<std::array<ll, 100>, 100>;
const int M = 1e9 + 7;

int n;

mat mul(mat a, mat b){
	mat res = {};

	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j)
			for(int k=0; k<n; ++k)
				res[i][j] += a[i][k]*b[k][j] % M;

	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j)
			res[i][j] %= M;

	return res;
}

int main(){
	int m, k; std::cin >> n >> m >> k;

	mat x = {};

	for(int i=0; i<m; ++i){
		int a, b; std::cin >> a >> b;
		++x[--a][--b];
	}

	mat u = {};

	for(int i=0; i<n; ++i) ++u[i][i];

	while(k){
		if(k&1) u = mul(u, x);
		x = mul(x, x);
		k /= 2;
	}

	std::cout << u[0][n-1] << '\n';
}
