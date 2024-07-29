#include <iostream>
#include <queue>
#include <array>

int m[1001][1001], delta[100001], bfs[1002001];
bool vis[1001][1001];

int main(){
	int h, w, q; std::cin >> h >> w >> q;

	for(int i=0; i<h; ++i)
		for(int j=0; j<w; ++j)
			std::cin >> m[i][j];

	std::priority_queue<std::array<int, 3>> pq;

	for(int i=0; i<h; ++i) pq.push({-m[i][0], i, 0});
	for(int i=0; i<h; ++i) pq.push({-m[i][w-1], i, w-1});
	for(int i=0; i<w; ++i) pq.push({-m[0][i], 0, i});
	for(int i=0; i<w; ++i) pq.push({-m[h-1][i], h-1, i});

	while((int)pq.size()){
		std::array<int, 3> f = pq.top(); pq.pop();

		if(vis[f[1]][f[2]]) continue;
		vis[f[1]][f[2]] = 1;

		int mn = 100001;
		if(f[2] && m[f[1]][f[2]-1] > m[f[1]][f[2]]) mn = std::min(mn, m[f[1]][f[2]-1]);
		if(f[1] && m[f[1]-1][f[2]] > m[f[1]][f[2]]) mn = std::min(mn, m[f[1]-1][f[2]]);
		if(f[2]<w-1 && m[f[1]][f[2]+1] > m[f[1]][f[2]]) mn = std::min(mn, m[f[1]][f[2]+1]);
		if(f[1]<h-1 && m[f[1]+1][f[2]] > m[f[1]][f[2]]) mn = std::min(mn, m[f[1]+1][f[2]]);

		if(mn < 100001 && f[1] && f[2] && f[1]<h-1 && f[2]<w-1) m[f[1]][f[2]] = mn;

		if(f[2] && m[f[1]][f[2]-1] <= m[f[1]][f[2]]) pq.push({-m[f[1]][f[2]-1], f[1], f[2]-1});
		if(f[1] && m[f[1]-1][f[2]] <= m[f[1]][f[2]]) pq.push({-m[f[1]-1][f[2]], f[1]-1, f[2]});

		if(f[2]<w-1 && m[f[1]][f[2]+1] <= m[f[1]][f[2]]) pq.push({-m[f[1]][f[2]+1], f[1], f[2]+1});
		if(f[1]<h-1 && m[f[1]+1][f[2]] <= m[f[1]][f[2]]) pq.push({-m[f[1]+1][f[2]], f[1]+1, f[2]});
	}

	for(int i=0; i<h; ++i)
		for(int j=0; j<w; ++j)
			++delta[m[i][j]];

	int curr = h*w;

	for(int i=1; i<=q; ++i){
		curr -= delta[i];
		std::cout << curr << '\n';
	}
}
