#include <iostream>

using ll = long long;

bool move[12][12], vis[12][12];
int h, w, k;
ll res;

void dfs(int i, int j, int k){
	if(k == 0) { ++res; return; }
	vis[i][j] = 1;
	if(move[i+1][j] && !vis[i+1][j]) dfs(i+1, j, k-1);
	if(move[i-1][j] && !vis[i-1][j]) dfs(i-1, j, k-1);
	if(move[i][j+1] && !vis[i][j+1]) dfs(i, j+1, k-1);
	if(move[i][j-1] && !vis[i][j-1]) dfs(i, j-1, k-1);
	vis[i][j] = 0;
}

int main(){
	std::cin >> h >> w >> k;
	for(int i=0; i<h; ++i)
		for(int j=0; j<w; ++j){
			char c; std::cin >> c;
			if(c == '.') move[i+1][j+1] = 1;
		}

	for(int i=1; i<=h; ++i)
		for(int j=1; j<=w; ++j)
			if(move[i][j]) dfs(i, j, k);

	std::cout << res << '\n';
}
