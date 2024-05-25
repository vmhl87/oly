#include <iostream>
#include <vector>
#include <stack>

void test_case(){
	int n, q; std::cin >> n >> q;
	int b[n]; for(int i=0; i<n; ++i) std::cin >> b[i];

	std::stack<int> adj[n];
	std::vector<int> ad[n];
	for(int i=1; i<n; ++i){
		int r, l; std::cin >> r >> l, --r, --l;
		adj[r].push(l), adj[l].push(r);
	}
	int parent[n] = {-1}, vis[n] = {};
	std::stack<int> dfs; dfs.push(0), vis[0] = 1;
	while(dfs.size()){
		if(adj[dfs.top()].size()){
			if(!vis[adj[dfs.top()].top()])
				vis[adj[dfs.top()].top()] = 1,
					parent[adj[dfs.top()].top()] = dfs.top(),
					ad[dfs.top()].push_back(adj[dfs.top()].top()),
					dfs.push(adj[dfs.top()].top());
			adj[dfs.top()].pop();
		}else dfs.pop();
	}
	
	int comp = 0, over = 0;
	int nei[n] = {}, lazy[n] = {}, ch1[n] = {}, ch2[n] = {}, ch3[n] = {}, ch4[n] = {};

	for(int i=0; i<n; ++i) if(b[i]){
		if(parent[i] != -1 && lazy[parent[i]]){
			for(int x : ad[parent[i]]) nei[x] += lazy[parent[i]];
			lazy[parent[i]] = 0;
		}
		// if no neighbors, node is new component
		if(nei[i] == 0) ++comp;
		// otherwise, it unites (nei) components
		else comp -= nei[i] - 1;
		// if more than 2 neighbors, node is overloaded
		if(nei[i] > 2) ++over;
		// iterate through neighbors
		if(parent[i] != -1){
			++nei[parent[i]];
			if(b[parent[i]] && nei[parent[i]] == 3) ++over;
		}
		over += ch2[i];
		ch4[i] = ch3[i], ch3[i] = ch2[i], ch2[i] = ch1[i];
		if(parent[i] != -1){
			if(nei[i] == 1) ++ch1[parent[i]];
			if(nei[i] == 2) ++ch2[parent[i]];
			if(nei[i] == 3) ++ch3[parent[i]];
			if(nei[i] == 4) ++ch4[parent[i]];
		}
	}

	while(q--){
		int u; std::cin >> u, --u;
		// if already active, shut off
		if(b[u]){
			// no longer active
			b[u] = 0;
			// if node was overloaded, reduce count
			if(nei[u] > 2) --over;
			// if they had no filled neighbors, they were their
			// own component
			if(nei[u] == 0) --comp;
			else comp += nei[u] - 1;
			for(int x : adj[u]){
				--nei[x];
				if(b[x] && nei[x] == 2) --over;
			}
		}else{
			b[u] = 1;
			if(nei[u] == 0) ++comp;
			else comp -= nei[u] - 1;
			if(nei[u] > 2) ++over;
			for(int x : adj[u]){
				++nei[x];
				if(b[x] && nei[x] == 3) ++over;
			}
		}
		if(comp == 1 && over == 0) std::cout << "Yes\n";
		else std::cout << "No\n";
	}
}

int main(){
	int t; std::cin >> t;
	while(t--) test_case();
}
