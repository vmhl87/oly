#include <iostream>
#include <vector>

using ll = long long;
const int maxn = 2e5;

std::vector<int> adj[maxn], bdj[maxn];

int under0[maxn], under1[maxn];
ll res;

void dfs(int i, int p){
	for(int x : adj[i]) if(x != p)
		dfs(x, i), under0[i] += under0[x], ++under0[i];

	for(int x : bdj[i]) if(x != p)
		dfs(x, i), under1[i] += under1[x], ++under1[i];

	res += (ll)(under0[i]) * (ll)(under1[i]);
	res += under0[i] + under1[i];
}

int over0[maxn], over1[maxn];

void dfs2(int i, int p){
	for(int x : adj[i]) if(x != p)
		over0[x] = over0[i] + under0[i] - under0[x],
		dfs2(x, i);

	for(int x : bdj[i]) if(x != p)
		over1[x] = over1[i] + under1[i] - under1[x],
		dfs2(x, i);

	res += (ll)(1+under0[i]) * (ll)(over1[i]);
	res += (ll)(1+under1[i]) * (ll)(over0[i]);
}

int main(){
	int n; std::cin >> n;

	for(int i=1; i<n; ++i){
		int a, b, t; std::cin >> a >> b >> t, --a, --b;

		if(t) bdj[a].push_back(b), bdj[b].push_back(a);
		else adj[a].push_back(b), adj[b].push_back(a);
	}

	dfs(0, 0), dfs2(0, 0);

	if(0) for(int i=0; i<n; ++i){
		std::cout << i+1 << " u0: " << under0[i] << " u1: " << under1[i] <<
			" o0: " << over0[i] << " o1: " << over1[i] << '\n';
	}

	std::cout << res << '\n';
}
