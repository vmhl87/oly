#include <iostream>
#include <array>

using ll = long long;
using mat = std::array<std::array<ll, 100>, 100>;

int n;

mat mul(mat a, mat b){
	mat res = {};

	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j)
			res[i][j] = 2e18;

	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j)
			for(int k=0; k<n; ++k)
				res[i][j] = std::min(res[i][j],
						a[i][k]+b[k][j]);

	return res;
}

int main(){
	int m, k; std::cin >> n >> m >> k;

	mat x = {};

	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j)
			x[i][j] = 2e18;

	for(int i=0; i<m; ++i){
		int a, b, c; std::cin >> a >> b >> c;
		--a, --b, x[a][b] = std::min(x[a][b], (ll) c);
	}

	mat u = {};

	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j)
			u[i][j] = x[i][j];

	--k;

	while(k){
		if(k&1) u = mul(u, x);
		x = mul(x, x);
		k /= 2;
	}

	if(u[0][n-1] == 2e18) std::cout << -1;
	else std::cout << u[0][n-1];
	std::cout << '\n';
}
