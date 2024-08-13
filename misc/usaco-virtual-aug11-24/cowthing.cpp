#include <iostream>
#include <vector>

std::vector<int> adj[100000];
int res;

void dfs(int i, int p){
	for(int x : adj[i]) if(x != p) dfs(x, i);

	int loc = (int)adj[i].size();
	if(p != -1) --loc;

	if(loc) res += std::__lg(loc)+1;
}

int main(){
	int n; std::cin >> n;
	for(int i=1; i<n; ++i){
		int a, b; std::cin >> a >> b, --a, --b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	res = n-1;

	dfs(0, -1);

	std::cout << res << '\n';
}
