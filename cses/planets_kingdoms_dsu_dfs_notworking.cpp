#include <iostream>
#include <stack>

int main(){
	int n, m; std::cin >> n >> m;

	std::stack<int> adj[n];

	while(m--){
		int a, b; std::cin >> a >> b;
		adj[a-1].push(b-1);
	}

	// dfs + dsu portion
	
	int root[n]; for(int i=0; i<n; ++i) root[i] = -1;

	int stack[n], len = 0;
	bool vis[n] = {}, instack[n] = {};
	int isc[n] = {};

	auto findroot = [&](int i){
		std::stack<int> a;

		while(root[i] != -1) a.push(i), i = root[i];

		while(a.size()) root[a.top()] = i, a.pop();

		return i;
	};
	

	for(int i=0; i<n; ++i) if(!vis[i]){
		stack[0] = i, len = 1;

		while(len){
			int t = stack[len-1];

			if(adj[t].size()){
				int next = adj[t].top(); adj[t].pop();

				if(vis[next]){
					if(isc[findroot(next)]){
					}

				}else if(instack[next]){
					for(int i=len-1; stack[i] != next; --i){

						root[stack[i]] = next, --isc[stack[i]], ++isc[next];
					}

				}else stack[len++] = next, instack[next] = 1;

			}else vis[t] = 1, --isc[findroot(stack[--len])], instack[stack[len]] = 0;
		}
	}
}
