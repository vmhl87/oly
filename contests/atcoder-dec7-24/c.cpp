#include <iostream>
#include <array>
#include <queue>

char a[1000][1000];
int d[1000][1000];

int main(){
	int h, w, D; std::cin >> h >> w >> D;

	for(int i=0; i<h; ++i)
		for(int j=0; j<w; ++j)
			std::cin >> a[i][j];

	std::queue<std::array<int, 2>> q;

	for(int i=0; i<h; ++i)
		for(int j=0; j<w; ++j)
			if(a[i][j] == 'H'){
				q.push({i, j});
				d[i][j] = D+1;
			}

	while(q.size()){
		int i = q.front()[0],
			j = q.front()[1];
		q.pop();

		if(d[i][j] == 1) continue;

		if(i-1 >= 0 && a[i-1][j] == '.' && !d[i-1][j])
			d[i-1][j] = d[i][j]-1, q.push({i-1, j});

		if(j-1 >= 0 && a[i][j-1] == '.' && !d[i][j-1])
			d[i][j-1] = d[i][j]-1, q.push({i, j-1});

		if(j+1 < w && a[i][j+1] == '.' && !d[i][j+1])
			d[i][j+1] = d[i][j]-1, q.push({i, j+1});

		if(i+1 < h && a[i+1][j] == '.' && !d[i+1][j])
			d[i+1][j] = d[i][j]-1, q.push({i+1, j});
	}

	int res = 0;

	for(int i=0; i<h; ++i)
		for(int j=0; j<w; ++j)
			if(d[i][j]) ++res;

	std::cout << res << '\n';
}
