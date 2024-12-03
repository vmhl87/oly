#include <iostream>
#include <vector>
#include <array>

std::vector<std::array<int, 3>> adj[10000];

bool v1[100][10001], v2[100][10001], v[100];

void dfs(int i){
	if(v[i]) return;
	v[i] = 1;

	for(const auto &[x, c, d] : adj[i]){
		dfs(x);

		for(int j=0; j<=10000-c; ++j)
			v1[i][j+c] |= v1[x][j];

		for(int j=0; j<=10000-d; ++j)
			v2[i][j+d] |= v2[x][j];
	}
}

int main(){
	freopen("meeting.in", "r", stdin);
	freopen("meeting.out", "w", stdout);

	int n, m; std::cin >> n >> m;

	for(int i=0; i<m; ++i){
		int x, y; std::cin >> x >> y;
		int c, d; std::cin >> c >> d;
		adj[--x].push_back({--y, c, d});
	}

	v1[n-1][0] = 1, v2[n-1][0] = 1;

	dfs(0);

	for(int i=0; i<=10000; ++i)
		if(v1[0][i] && v2[0][i])
			std::cout << i << '\n', exit(0);

	std::cout << "IMPOSSIBLE\n";
}
