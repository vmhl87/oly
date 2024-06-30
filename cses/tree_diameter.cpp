#include <iostream>
#include <stack>

int main(){
	int n; std::cin >> n;

	std::stack<int> adj[n];

	for(int i=1; i<n; ++i){
		int a, b; std::cin >> a >> b, --a, --b;

		adj[a].push(b), adj[b].push(a);
	}

	std::stack<int> dfs; dfs.push(0);
	bool vis[n];
	
	int cand[n][2], best = 0;
	for(int i=0; i<n; ++i) cand[i][0] = 0, cand[i][1] = 0, vis[i] = 0; vis[0] = 1;

	while(dfs.size()){
		int t = dfs.top();

		if(adj[t].size()){
			int next = adj[t].top(); adj[t].pop();

			if(!vis[next]) dfs.push(next), vis[next] = 1;

		}else{
			best = std::max(best, cand[t][0]+cand[t][1]);

			dfs.pop();
			
			if(dfs.size()){
				int cur = dfs.top();
				
				if(cand[t][1]+1 > cand[cur][0]){
					cand[cur][0] = cand[t][1]+1;
					
					if(cand[cur][0] > cand[cur][1]){
						t = cand[cur][0];
						cand[cur][0] = cand[cur][1], cand[cur][1] = t;
					}
				}
			}
		}
	}
	
	std::cout << best << '\n';
}
