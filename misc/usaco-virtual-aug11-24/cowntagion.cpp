// feels like there is some dp that can be done here
// balance somehow between stay @ 1 and multiply +
// send cow down some length then multiply there
//
// i think this exists in star graph?
//
//                   1
//                   2
//                   3
//                   4
//                   5
//                 9 6 8
//                   7
//
// 1. -> 2
// 2. -> 3
// 3. -> 4
// 4. x2
// 5. x2 (4)
// 6. x2 (8)
// 7. x2 (16)
// 1 + 2 + 3 + 4 + 5 + 6 + 6 + 6
// -> 7 + 10 + 5 + 18
//    12 + 18 + 10 = 40
//
// instead:
// 1. x2
// 2. x2
// 3. x2
// 4. x2
// 1 + 2 + 3 + 4 + 5 + 6*3
// -> 4 + 10 + 5 + 18
//    19 + 18
//    bruh what
// 
// wait is it just centroid of graph??
// tree dp i feel like hm

#include <iostream>
#include <vector>

using LL = long long;

std::vector<int> adj[100000];
int par[100000], count[100000], depth[100000];
ll lo[100000], hi[100000];

void dfs(int i, int p){
	for(int x : adj[i]) if(x != p){
		depth[x] = depth[i] + 1;
		par[x] = i, dfs(x, i);
		lo[i] += lo[x] + count[x] + 1;
		count[i] += count[x] + 1;
	}
}

void dfs2(int i, int p){
	ll comp = 0;
	for(int x : adj[i]) if(x != p){
		hi[x] += comp;
		comp += lo[x]
	}
	for(int x : adj[i]) if(x != p) dfs(x, i);
}

int main(){
	int n; std::cin >> n;
	for(int i=1; i<n; ++i){
		int a, b; std::cin >> a >> b, --a, --b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	dfs(0, -1);
	dfs2(0, -1);
}
