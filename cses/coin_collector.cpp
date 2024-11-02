#include <iostream>
#include <vector>

using ll = long long;

std::vector<int> adj[100000];
int k[100000];

int loc[100000], link[100000], idx=1;
std::vector<int> s;
bool in[100000];

int scc[100000], sidx;
ll sz[100000];
std::vector<int> sdj[100000];

void dfs(int v){
	loc[v] = idx;
	link[v] = idx;
	++idx;

	s.push_back(v);
	in[v] = 1;

	for(int x : adj[v]){
		if(!loc[x]){
			dfs(x);
			link[v] = std::min(link[v], link[x]);
		}else if(in[x])
			link[v] = std::min(link[v], loc[x]);
	}

	if(link[v] == loc[v]){
		scc[v] = sidx, sz[sidx] += k[v];
		while(v != s.back()){
			scc[s.back()] = sidx;
			sz[sidx] += k[s.back()];
			in[s.back()] = 0;
			s.pop_back();
		}
		s.pop_back();
		in[v] = 0;
		++sidx;
	}
}

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int n, m; std::cin >> n >> m;
	for(int i=0; i<n; ++i) std::cin >> k[i];
	while(m--){
		int a, b; std::cin >> a >> b;
		adj[a-1].push_back(b-1);
	}

	for(int i=0; i<n; ++i) if(!loc[i]) dfs(i);

	for(int i=0; i<n; ++i)
		for(int x : adj[i]) if(scc[x] != scc[i])
			sdj[scc[x]].push_back(scc[i]);

	for(int i=sidx-1; i>=0; --i){
		ll max = 0;
		for(int x : sdj[i])
			max = std::max(max, sz[x]);
		sz[i] += max;
	}

	ll best = 0;
	for(int i=0; i<sidx; ++i)
		best = std::max(best, sz[i]);

	std::cout << best << '\n';
}
