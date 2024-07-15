#include <iostream>
#include <vector>

int* dfs(int i, int p, std::vector<int> *adj, int *path){
	int v = *path;

	for(int x : adj[i]) if(x != p)
		*(++path) = v+1, *(path = dfs(x, i, adj, path)) = v+1;

	return ++path;
}

int main(){
	int n; std::cin >> n;

	int path[n<<1] = {};
	std::vector<int> adj[n];

	for(int i=1; i<n; ++i){
		int a, b; std::cin >> a >> b;
		adj[a].push_back(b), adj[b].push_back(a);
	}

	for(int i=0; i<n; ++i){
		dfs(i, -1, adj, path);

		int max = 0;
		for(int x : path) max = max > x ? max : x;

		std::cout << '\n';

		for(int l=max, par=0; l+1; --l, std::cout << '\n')
			for(int x : path)
				std::cout << (x == l ? "\\/"[par^=1] : ' ');
	}

	std::cout << '\n';
}
