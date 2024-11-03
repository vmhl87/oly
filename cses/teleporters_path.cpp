#include <iostream>
#include <vector>

int res[200000], indeg[200000], outdeg[200000], *p = res;
std::vector<int> adj[200000];

void dfs(int i){
	while(adj[i].size()){
		int j = adj[i].back();
		adj[i].pop_back();
		dfs(j);
	}
	*(p++) = i;
}

int main(){
	int n, m; std::cin >> n >> m;
	for(int i=0; i<m; ++i){
		int a, b; std::cin >> a >> b;
		adj[a-1].push_back(b-1);
		++outdeg[a-1], ++indeg[b-1];
	}

	for(int i=1; i<n-1; ++i)
		if(indeg[i] != outdeg[i])
			std::cout << "IMPOSSIBLE\n", exit(0);

	if(indeg[0] != outdeg[0]-1)
		std::cout << "IMPOSSIBLE\n", exit(0);

	if(indeg[n-1]-1 != outdeg[n-1])
		std::cout << "IMPOSSIBLE\n", exit(0);

	dfs(0);

	if(p != res+m+1 || res[0] != n-1)
		std::cout << "IMPOSSIBLE\n", exit(0);

	std::cout << 1 << ' ';
	for(int i=m-1; i>=0; --i)
		std::cout << res[i]+1 << " \n"[i==0];
}
