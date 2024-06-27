#include <iostream>
#include <vector>
#include <stack>

int main(){
	int n, m; std::cin >> n >> m;

	std::vector<int> adj[n];

	for(int i=0; i<m; ++i){
		int a, b; std::cin >> a >> b, --a, --b;

		adj[a].push_back(b), adj[b].push_back(a);
	}

	int at[n] = {};
	bool vis[n] = {}, bridge[n] = {};

	int parent[n] = {-1}, delta[n] = {}, now = 0;

	std::stack<int> dfs, par; dfs.push(0);

	while(dfs.size()){
		int top = dfs.top();
		vis[top] = 1;

		if(at[top] == adj[top].size()){
			dfs.pop(), par.pop();

			now += delta[top];

			if(now == 0) bridge[top] = 1;
		}else{
			int next = adj[top][at[top]];
			if(!vis[next]){
				dfs.push(next), par.push(top);

				parent[next] = top;
			}else if(par.size() && par.top() != next){
				// process back edge
				++delta[top];
				--delta[next];
			}

			++at[top];
		}
	}

	for(int i : parent) std::cout << i+1 << ' '; std::cout << '\n';

	for(int i=0; i<n; ++i) if(bridge[i])
		std::cout << i+1 << ' ' << parent[i]+1 << '\n';
}
