#include <iostream>

using ll = long long;
constexpr int MOD = 1e9 + 7;

bool adj[20][20];
ll way[20][1<<20];
int n;

//ll dfs(int i, int j){
//	if(i == n-1 && j == (1<<n)-1) return 1;
//	if(way[i][j]) return way[i][j] - 1;
//	ll res = 0;
//	for(int x=0; x<n; ++x) if(!((j>>x)&1))
//		if(adj[i][x]) res += dfs(x, 1<<x|j);
//	way[i][j] = (res % MOD) + 1;
//	return res % MOD;
//}

ll dfs(int i, int j){
	if(i == 0 && j == 1) return 1;
	if(way[i][j]) return way[i][j] - 1;
	ll res = 0;
	for(int x=0; x<n; ++x) if((j>>x) & 1)
		if(adj[x][i]) res += dfs(x, j ^ (1<<i));
	way[i][j] = (res % MOD) + 1;
	return res % MOD;
}

int main(){
	int m; std::cin >> n >> m;
	while(m--){
		int a, b; std::cin >> a >> b;
		adj[a-1][b-1] = 1;
	}

	//std::cout << dfs(0, 1) << '\n';
	std::cout << dfs(n-1, (1<<n) - 1) << '\n';
}
