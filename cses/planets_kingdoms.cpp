#include <iostream>
#include <stack>
 
int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int n, m; std::cin >> n >> m;
 
	std::stack<int> adj[n];
 
	while(m--){
		int a, b; std::cin >> a >> b;
		adj[a-1].push(b-1);
	}
 
	int root[n]; for(int i=0; i<n; ++i) root[i] = i;
 
	int stack[n], len = 0;
	bool vis[n] = {}, instack[n] = {};
	int isc[n] = {};
	
	for(int i=0; i<n; ++i) if(!vis[i]){
		stack[0] = i, len = 1, ++isc[root[i]], instack[i] = 1;

		int sm = 1;
 
		while(len){
			int t = stack[len-1];
 
			if(adj[t].size()){
				int next = adj[t].top(); adj[t].pop();
 
				if(vis[next]){
					if(isc[root[next]]) for(int j=len-1; root[stack[j]] != root[next]; --j)
						--isc[root[stack[j]]], root[stack[j]] = root[next], ++isc[root[next]];
 
				}else if(instack[next]){
					for(int j=len-1; root[stack[j]] != root[next]; --j)
						--isc[root[stack[j]]], root[stack[j]] = root[next], ++isc[root[next]];
 
				}else ++isc[root[next]], instack[next] = 1, stack[len++] = next, ++sm;
 
			}else vis[t] = 1, --isc[root[t]], instack[t] = 0, --len, --sm;
		}
	}
 
	// for(int i : root) std::cout << i << ' '; std::cout << '\n';
 
	int which[n] = {}, count = 0;
 
	for(int i=0; i<n; ++i){
		int f = i;

		while(which[f] == 0 && root[f] != f) f = root[f];

		if(which[f] == 0) which[f] = ++count;

		which[i] = which[f];
	}
 
	std::cout << count << '\n';
 
	for(int i=0; i<n; ++i){
		if(i) std::cout << ' ';
 
		std::cout << which[i];
	}
 
	std::cout << '\n';
}
