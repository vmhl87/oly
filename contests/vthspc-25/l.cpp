#include <iostream>
#include <vector>

const int N = 1e5;

std::vector<int> adj[N];
int tm[N], t;
bool vis[N];

void move(int i, int j){
	// std::cout << i+1 << '-' << j+1 << ' ';
	std::cout << i+1 << ' ';
}

void dfs(int i){
	tm[i] = ++t;
	vis[i] = 1;

	for(int j : adj[i]){
		if(!vis[j]) move(i, j), dfs(j), move(j, i);
		else if(tm[i] < tm[j]) move(i, j), move(j, i);
	}
}

int main(){
	int n, c; std::cin >> n >> c;

	while(c--){
		int a, b; std::cin >> a >> b, --a, --b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	
	dfs(0);
	std::cout << 1 << '\n';
}
