#include <iostream>
#include <stack>
#include <cmath>

void test_case(){
	int n, a, b; std::cin >> n >> a >> b, --a, --b;
	std::stack<int> adj[n];
	for(int i=1; i<n; ++i){
		int r, l; std::cin >> r >> l, --r, --l;
		adj[r].push(l), adj[l].push(r);
	}
	bool vis[n] = {};
	std::stack<int> dfs; dfs.push(a), vis[a] = 1;
	int maxlen = 1, dist = 0;
	while(dfs.size()){
		if(dfs.top() == b) dist = dfs.size() - 1;
		if(adj[dfs.top()].size()){
			if(!vis[adj[dfs.top()].top()])
				maxlen = std::max(maxlen, (int)dfs.size()),
					   vis[adj[dfs.top()].top()] = 1,
					   dfs.push(adj[dfs.top()].top());
			adj[dfs.top()].pop();
		}
		else dfs.pop();
	}
	std::cout << ((n-1)<<1) + ((dist+1)>>1) - maxlen << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test_case();
}
