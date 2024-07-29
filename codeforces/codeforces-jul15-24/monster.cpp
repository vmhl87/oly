#include <iostream>
#include <vector>

using LL = long long;

int n;
std::vector<int> adj[300001];
LL a[300001], zero[300001], one[300001], cost;
int picked[300001];

void dfs(int i, int p){
	for(int x : adj[i]) if(x != p) dfs(x, i);

	one[i] = a[i];
	for(int x : adj[i]) if(x != p) one[i] += zero[x];

	zero[i] = 0;
	for(int x : adj[i]) if(x != p) zero[i] += std::max(one[x], zero[x]);
}

void dfs2(int i, int p){
	if(picked[i]){
		for(int x : adj[i]) if(x != p) picked[x] = 0;
	}else{
		for(int x : adj[i]) if(x != p) picked[x] = one[x] > zero[x];
	}

	int c = 0;
	for(int x : adj[i]) if(x != p) dfs2(x, i), ++c;

	if(!picked[i]){
		one[i] = a[i];
		for(int x : adj[i]) if(x != p && !picked[x]) one[i] += zero[x];

		zero[i] = 0;
		for(int x : adj[i]) if(x != p && !picked[x]) zero[i] += std::max(one[x], zero[x]);

		if(p == -1 || picked[p]) cost += std::max(one[i], zero[i]);
	}
}

void test_case(){
	std::cin >> n;

	for(int i=0; i<n; ++i) adj[i].clear(), std::cin >> a[i];

	for(int i=1; i<n; ++i){
		int l, r; std::cin >> l >> r, --l, --r;
		adj[l].push_back(r), adj[r].push_back(l);
	}

	dfs(0, -1);

	LL all = 0;
	for(int i=0; i<n; ++i) all += a[i];
	LL part = all - std::max(one[0], zero[0]);

	cost = 0;
	picked[0] = (one[0] > zero[0] ? 1 : 0);

	dfs2(0, -1);

	if(cost) cost = part - cost;

	std::cout << all + part + cost << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test_case();
}
