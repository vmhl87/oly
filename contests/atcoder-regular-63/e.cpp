// Initially I started writing "tree dp" for this task
// because I thought it was somehow necessary. It in the
// end worked out to a greedy that is essentially identical
// to multisource bfs. Fun though

#include <iostream>
#include <vector>
#include <array>

const int N = 1e5;

std::vector<int> adj[N];

bool k[N];
int p[N];

void fail() { std::cout << "No\n", exit(0); }

std::array<int, 2> down[N];

std::array<int, 2> merge(std::array<int, 2> a, std::array<int, 2> B){
	if(B[0] == -1 && B[1] == -1) return a;

	std::array<int, 2> b = {B[0]-1, B[1]+1};

	if(a[0] == -1 && a[1] == -1) return b;

	if((a[0]&1) != (b[0]&1)) fail();

	std::array<int, 2> res = {
		std::max(a[0], b[0]),
		std::min(a[1], b[1])
	};

	if(res[0] > res[1]) fail();

	return res;
}

void dfs1(int i, int p){
	for(int x : adj[i]) if(x != p){
		dfs1(x, i);
		if(!k[i]) down[i] = merge(down[i], down[x]);
	}
}

void dfs2(int i, int p){
	if(i != p) down[i] = merge(down[i], down[p]);

	for(int x : adj[i]) if(x != p)
		dfs2(x, i);
}

int main(){
	int n; std::cin >> n;

	for(int i=1; i<n; ++i){
		int a, b; std::cin >> a >> b;
		adj[--a].push_back(--b);
		adj[b].push_back(a);
	}

	for(int i=0; i<n; ++i)
		down[i] = {-1, -1};

	int s;

	int K; std::cin >> K;
	for(int i=0; i<K; ++i){
		int a, b; std::cin >> a >> b, --a;
		k[a] = 1, p[a] = b;
		down[a] = {b, b};
		s = a;
	}

	dfs1(s, s);
	dfs2(s, s);

	std::cout << "Yes\n";

	for(int i=0; i<n; ++i)
		std::cout << down[i][0] /*<< ' ' << down[i][1]*/ << '\n';
}
