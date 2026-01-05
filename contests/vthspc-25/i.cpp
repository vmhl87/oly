#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <map>

using ll = long long;
const int N = 2e5;

std::vector<std::vector<std::pair<ll, ll>>> rec[N];
std::vector<int> adj[N], ord;

bool vis[N], real[N];
ll best[N];

void dfs(int i){
	vis[i] = 1;

	for(int j : adj[i]) if(!vis[j]) dfs(j);

	ord.push_back(i);
}

int main(){
	int n, k; std::cin >> n >> k;

	std::map<std::string, int> M;

	for(int i=0; i<n; ++i){
		int j; std::cin >> j;
		std::string s; std::cin >> s;
		int S = M.count(s) ? M[s] : M.size(); M[s] = S;

		rec[S].push_back({});

		while(j--){
			int c; std::string v;
			std::cin >> c >> v;
			int V = M.count(v) ? M[v] : M.size(); M[v] = V;
			rec[S].back().push_back({V, c});
			adj[S].push_back(V);
			// adj[V].push_back(S);
		}
	}

	for(int i=0; i<k; ++i){
		int c; std::string v;
		std::cin >> c >> v;
		int V = M.count(v) ? M[v] : M.size(); M[v] = V;
		best[V] = c, real[V] = 1;
	}

	assert(M.count("pickaxe") != 0);
	int t = M["pickaxe"];

	for(int i=0; i<M.size(); ++i) if(!vis[i]) dfs(i);

	/*
	std::cout << '\n' << '\n';

	for(int i=0; i<M.size(); ++i){
		std::cout << i << ": ";
		for(int j : adj[i]) std::cout << j << ' ';
		std::cout << '\n';
	}

	std::cout << '\n' << '\n';

	for(const auto &[v, c] : M) std::cout << v << ": " << c << '\n';

	std::cout << '\n' << '\n';

	for(int i : ord) std::cout << i << ' ';
	std::cout << '\n';

	std::cout << '\n' << '\n';
	*/

	for(int i : ord){
		for(const auto &v : rec[i]){
			ll cost = 0;
			for(const auto &[type, count] : v)
				assert(real[type]), cost += best[type] * count;
			if(cost < best[i] || !real[i])
				best[i] = cost, real[i] = 1;
		}
	}

	std::cout << best[t] << '\n';
}
