#include <iostream>
#include <vector>
#include <array>
#include <queue>

std::vector<std::array<int, 3>> adj[500][500][2];
int v[500][500][2];
char a[500][500];

int main(){
	int h, w; std::cin >> h >> w;

	for(int i=0; i<h; ++i)
		for(int j=0; j<w; ++j)
			std::cin >> a[i][j];

	auto blocked = [] (int i, int j, int x) {
		if(a[i][j] == '#') return 1;
		if(a[i][j] == 'o' && x) return 1;
		if(a[i][j] == 'x' && !x) return 1;
		return 0;
	};

	for(int i=0; i<h; ++i)
		for(int j=0; j<w; ++j)
			for(int x=0; x<2; ++x){
				if(blocked(i, j, x)) continue;

#define add(X, Y, Z) adj[i][j][x].push_back({X, Y, a[X][Y] == '?' ? 1-Z : Z})
//#define add(X, Y, Z) adj[i][j][x].push_back({X, Y, Z})

				if(i) add(i-1, j, x);
				if(j) add(i, j-1, x);

				if(i+1 < h) add(i+1, j, x);
				if(j+1 < w) add(i, j+1, x);
			}

	int best = 1e9;
	std::queue<std::array<int, 3>> bfs;

	for(int i=0; i<h; ++i)
		for(int j=0; j<w; ++j)
			if(a[i][j] == 'S'){
				for(int k=0; k<h; ++k)
					for(int l=0; l<w; ++l)
						v[k][l][0] = 1e9, v[k][l][1] = 1e9;

				bfs.push({i, j, 0});
				v[i][j][0] = 0;

				while(bfs.size()){
					std::array<int, 3> t = bfs.front();
					bfs.pop();

					for(const auto &[k, l, m] : adj[t[0]][t[1]][t[2]])
						if(v[k][l][m] == 1e9)
							v[k][l][m] = v[t[0]][t[1]][t[2]]+1,
								bfs.push({k, l, m});
				}

				for(int k=0; k<h; ++k)
					for(int l=0; l<w; ++l)
						for(int m=0; m<2; ++m)
							if(a[k][l] == 'G')
								best = std::min(best, v[k][l][m]);
			}

	std::cout << (best == 1e9 ? -1 : best) << '\n';
}
