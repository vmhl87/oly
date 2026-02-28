#include <iostream>
#include <queue>
#include <array>

const int N = 2e3;

char a[N][N];
bool v[N][N];
int d[N][N];

void test(){
	int n, m; std::cin >> n >> m;

	for(int i=0; i<m; ++i)
		for(int j=0; j<n; ++j)
			std::cin >> a[i][j], v[i][j] = 1, d[i][j] = 1e9;

	for(int i=0; i<m; ++i)
		for(int j=0; j<n; ++j)
			if(a[i][j] > '0' && a[i][j] <= '9'){
				int d = a[i][j] - '0';
				for(int ii=0; ii<m; ++ii)
					for(int jj=0; jj<n; ++jj)
						if((i-ii)*(i-ii) + (j-jj)*(j-jj) <= d*d + d)
							v[ii][jj] = 0;
			}

	std::queue<std::array<int, 2>> bfs;

	for(int i=0; i<m; ++i)
		for(int j=0; j<n; ++j)
			if(a[i][j] == 'P') bfs.push({i, j}), d[i][j] = 0;

	while(bfs.size()){
		auto [i, j] = bfs.front();
		bfs.pop();

		auto t = [&] (int y, int x) {
			if(y >= 0 && y < m && x >= 0 && x < n && v[y][x] && d[y][x] == 1e9){
				d[y][x] = d[i][j] + 1;
				bfs.push({y, x});
			}
		};

		t(i-1, j);
		t(i+1, j);
		t(i, j-1);
		t(i, j+1);
	}

	for(int i=0; i<m; ++i)
		for(int j=0; j<n; ++j)
			if(a[i][j] == 'D') std::cout << d[i][j] << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
