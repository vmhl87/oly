#include <iostream>
#include <vector>
#include <array>

std::vector<std::vector<char>> b;
std::vector<std::vector<std::vector<std::array<int, 2>>>> adj;
std::vector<std::vector<std::array<int, 3>>> ct;

using ll = long long;
ll res = 0;

void merge(std::array<int, 2> a, std::array<int, 2> b){
	adj[a[0]][a[1]].push_back(b);
	adj[b[0]][b[1]].push_back(a);
}

std::vector<std::vector<bool>> vis, bp;

using a2 = std::array<int, 2>;

void dfs(a2 i, a2 r){
	vis[i[0]][i[1]] = 1;
	++ct[r[0]][r[1]][bp[i[0]][i[1]]];

	for(const auto &[x, y] : adj[i[0]][i[1]]){
		if(!vis[x][y]){
			bp[x][y] = 1^bp[i[0]][i[1]];
			dfs({x, y}, r);
		}else if(bp[x][y] != 1^bp[i[0]][i[1]]){
			ct[r[0]][r[1]][2] = 1;
		}
	}
}

int main(){
	int n, m, x, y; std::cin >> n >> m >> x >> y;

	b.resize(n, std::vector<char>(m));
	adj.resize(n, std::vector<std::vector<std::array<int, 2>>>(m));
	vis.resize(n, std::vector<bool>(m, 0));
	bp.resize(n, std::vector<bool>(m, 0));
	ct.resize(n, std::vector<std::array<int, 3>>(m));

	for(int i=0; i<n; ++i)
		for(int j=0; j<m; ++j)
			std::cin >> b[i][j];

	int q; std::cin >> q;

	for(int i=0; i<n; ++i){
		int run = 0;
		for(int j=0; j<m; ++j){
			if(b[i][j] == '*'){
				++run;
				if(j>=y && run>y)
					merge({i, j}, {i, j-y});
			}else{
				run = 0;
			}
		}
	}

	for(int i=0; i<m; ++i){
		int run = 0;
		for(int j=0; j<n; ++j){
			if(b[j][i] == '*'){
				++run;
				if(j>=x && run>x)
					merge({j, i}, {j-x, i});
			}else{
				run = 0;
			}
		}
	}

	for(int i=0; i<n; ++i)
		for(int j=0; j<m; ++j)
			if(!vis[i][j]){
				dfs({i, j}, {i, j});
				if(ct[i][j][2]){
					ll sz = ct[i][j][0] + ct[i][j][1];
					res += (sz*(sz-1))/2;
				}else{
					ll sz = ct[i][j][0];
					res += (sz*(sz-1))/2;
					sz = ct[i][j][1];
					res += (sz*(sz-1))/2;
				}
			}

	std::cout << res*2 << '\n';

	/*
	for(int i=0; i<n; ++i){
		for(int j=0; j<m; ++j){
			for(const auto &[x, y] : adj[i][j]){
				std::cout << '(' << i << ' ' << j << ") -> (" << x << ' ' << y << ")\n";
			}
		}
	}
	*/
}
