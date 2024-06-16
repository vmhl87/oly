#include <iostream>
#include <vector>
#include <stack>

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int n, q; std::cin >> n >> q;

	int to[n];
	for(int i=0; i<n; ++i) std::cin >> to[i], --to[i];

	int depth[n], jump[n], cyloc[n], cypos[n];
	std::vector<std::vector<int>> cyc;

	bool vis[n] = {};
	for(int i=0; i<n; ++i) if(!vis[i]){
		std::stack<int> chain; chain.push(i);

		while(!vis[chain.top()])
			vis[chain.top()] = 1, depth[chain.top()] = -1, chain.push(to[chain.top()]);

		if(depth[chain.top()] == -1){
			std::vector<int> cycle;

			cycle.push_back(chain.top()), chain.pop();

			while(chain.top() != cycle[0]) cycle.push_back(chain.top()), chain.pop();

			for(int j=0; j<(int)cycle.size(); ++j)
				depth[cycle[j]] = 0, jump[cycle[j]] = cycle[j],
					cyloc[cycle[j]] = j, cypos[cycle[j]] = cyc.size();

			cyc.push_back(cycle);
		}

		chain.pop();

		while(chain.size()){
			int x = chain.top(); chain.pop();

			depth[x] = depth[to[x]] + 1;

			if(depth[to[x]] + depth[jump[jump[to[x]]]] == depth[jump[to[x]]]<<1)
				jump[x] = jump[jump[to[x]]];
			else jump[x] = to[x];
		}
	}

	while(q--){
		int x, k; std::cin >> x >> k, --x;

		if(k > depth[x]){
			k -= depth[x];

			while(depth[x]) x = jump[x];

			int idx = (cyloc[x]-k) % (int)cyc[cypos[x]].size();
			if(idx < 0) idx += (int)cyc[cypos[x]].size();

			std::cout << cyc[cypos[x]][idx]+1 << '\n';
		}else{
			k = depth[x] - k;

			while(depth[x] > k){
				if(depth[jump[x]] < k) x = to[x];
				else x = jump[x];
			}

			std::cout << x+1 << '\n';
		}
	}
}
