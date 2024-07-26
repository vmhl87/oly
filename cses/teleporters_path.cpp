// UNFINISHED

#include <iostream>
#include <vector>

std::vector<int> adj[200000];

int main(){
	int n, m; std::cin >> n >> m;
	for(int i=0; i<m; ++i){
		int a, b; std::cin >> a >> b;
		adj[a-1].push_back(b-1);
	}

	std::vector<int> dir;
	int at = 0; dir.push_back(0);
	while(adj[at].size()) dir.push_back(adj[at].back()),
		adj[at].pop_back(), at = dir.back();

	std::vector<int> sol;
	for(int x : dir){
		sol.push_back(x);
		int at = x;
		while(adj[at].size()) sol.push_back(adj[at].back()),
			adj[at].pop_back(), at = sol.back();
		if(at != x) break;
	}

	if(sol.size() != m+1 || sol.back() != n-1) std::cout << "IMPOSSIBLE\n";
	else for(int i=0; i<=m; ++i) std::cout << sol[i]+1 << " \n"[i==m];
}
