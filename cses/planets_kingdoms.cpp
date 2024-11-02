#include <iostream>
#include <vector>

std::vector<int> adj[100000];

int loc[100000], low[100000], pos=1;
std::vector<int> s;
bool in[100000];

int k[100000], ki;

void dfs(int i){
	loc[i] = low[i] = pos++;

	s.push_back(i);
	in[i] = 1;

	for(int x : adj[i])
		if(!loc[x]) dfs(x), low[i] = std::min(low[i], low[x]);
		else if(in[x]) low[i] = std::min(low[i], loc[x]);

	if(low[i] == loc[i]){
		++ki;
		int v = -1;
		while(v != i){
			v = s.back();
			k[v] = ki, in[v] = 0;
			s.pop_back();
		}
	}
}

int main(){
	int n, m; std::cin >> n >> m;
	while(m--){
		int a, b; std::cin >> a >> b;
		adj[a-1].push_back(b-1);
	}

	for(int i=0; i<n; ++i) if(!loc[i]) dfs(i);

	std::cout << ki << '\n';
	for(int i=0; i<n; ++i) std::cout << k[i] << " \n"[i==n-1];
}
