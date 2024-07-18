// Independent Set  -  https://dmoj.ca/problem/dpp
// Educational DP Contest AtCoder
//
// tree dp - store for each node the # of ways to
// color its subtree if it is a) colored white and
// b) colored black: propagation is pretty simple

#include <iostream>
#include <vector>

using LL = long long;

constexpr int M = 1e9 + 7;
std::vector<int> adj[100000];
LL w[100000], b[100000];

void dfs(int i, int p){
	for(int x : adj[i]) if(x != p) dfs(x, i);

	w[i] = 1, b[i] = 1;

	for(int x : adj[i]) if(x != p){
		// not using paren here is kind of sketchy
		// but proof by AC /shrug
		b[i] = b[i] * w[x] % M;
		w[i] = w[i] * (w[x] + b[x]) % M;
	}
}

int main(){
	int n; std::cin >> n;

	for(int i=1; i<n; ++i){
		int a, b; std::cin >> a >> b, --a, --b;
		adj[a].push_back(b), adj[b].push_back(a);
	}

	dfs(0, -1);

	std::cout << (w[0] + b[0]) % M << '\n';
}
