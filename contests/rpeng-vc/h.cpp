#include <iostream>

using ll = long long;
const int m = 1e9 + 7;

int a[100][100], r, c;

ll d[100][100];
bool v[100][100];

ll f(int x, int y){
	if(x == r-1 && y == c-1) return 1;

	if(v[x][y]) return d[x][y];
	v[x][y] = 1;

	for(int i=x+1; i<r; ++i)
		for(int j=y+1; j<c; ++j)
			if(a[x][y] != a[i][j])
				d[x][y] = (d[x][y] + f(i, j)) % m;

	return d[x][y];
}

int main(){
	freopen("hopscotch.in", "r", stdin);
	freopen("hopscotch.out", "w", stdout);

	int k; std::cin >> r >> c >> k;

	for(int i=0; i<r; ++i)
		for(int j=0; j<c; ++j)
			std::cin >> a[i][j];

	std::cout << f(0, 0) << '\n';
}
