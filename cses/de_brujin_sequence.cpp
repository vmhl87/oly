#include <iostream>
#include <vector>

std::vector<int> adj[1<<15], res;

void dfs(int i){
	while(adj[i].size()){
		int n = adj[i].back();
		adj[i].pop_back();
		dfs(n);
	}
	std::cout << (i&1);
}

int main(){
	int n; std::cin >> n, --n;

	if(!n) std::cout << "01\n", exit(0);

	for(int i=0; i<1<<n; ++i){
		adj[i].push_back((i*2) % (1<<n));
		adj[i].push_back((i*2+1) % (1<<n));
	}

	dfs(0);
	for(int i=1; i<n; ++i) std::cout << 0;
	std::cout << '\n';
}
