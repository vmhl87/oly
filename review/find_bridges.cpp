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

	int at[n] = {}, depth[n] = {1};
	bool bridge[n] = {};

	int parent[n] = {-1}, delta[n] = {}, now = 0;

	std::stack<int> dfs, par; dfs.push(0);

	while(dfs.size()){
		int top = dfs.top();

		if(at[top] == adj[top].size()){
			dfs.pop(), par.pop();

			now += delta[top];

			if(dfs.size()){
				if(now == 0) bridge[top] = 1;

				delta[dfs.top()] += now, now = 0;
			}
		}else{
			int next = adj[top][at[top]];
			if(!depth[next]){
				dfs.push(next), par.push(top);

				parent[next] = top, depth[next] = depth[top] + 1;
			}else if(par.size() && par.top() != next && depth[next] < depth[top]){
				++delta[top];
				--delta[next];

				std::cout << "Back edge: " << top+1 << ' ' << next+1 << '\n';
			}

			++at[top];
		}
	}

	std::cout << "Parents:\n";
	for(int i : parent) std::cout << i+1 << ' '; std::cout << '\n';

	std::cout << "Bridges:\n";
	for(int i=0; i<n; ++i) if(bridge[i])
		std::cout << i+1 << ' ' << parent[i]+1 << '\n';
}
