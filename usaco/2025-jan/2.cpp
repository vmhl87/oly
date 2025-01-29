#include <iostream>
#include <vector>

using ll = long long;
const int N = 2e5;

std::vector<int> adj[N];
int root[N], size[N];
ll comp;

ll sz(int j){
	ll i = size[j];
	return (i*(i-1))/2;
}

int find(int i){
	if(root[i] < 0) return i;
	return root[i] = find(root[i]);
}

void merge(int a, int b){
	if((a = find(a)) == (b = find(b))) return;
	comp -= sz(a) + sz(b);
	if(root[a] > root[b]) std::swap(a, b);
	size[a] += size[b];
	root[a] += root[b];
	root[b] = a;
	comp += sz(a);
}

char s[N];
ll res[N];

int main(){
	int n, m; std::cin >> n >> m;
	for(int i=0; i<n; ++i) std::cin >> s[i], root[i] = -1;

	while(m--){
		int a, b; std::cin >> a >> b;
		adj[--a].push_back(--b);
		adj[b].push_back(a);
		if(s[a] == '1' && s[b] == '1')
			merge(a, b);
	}

	for(int i=n-1; i>=0; --i){
		if(s[i] == '0')
			for(int x : adj[i])
				if(s[x] == '1' || x > i)
					merge(i, x);
		res[i] += comp += size[find(i)]++;
	}

	for(int i=0; i<n; ++i) std::cout << res[i] << '\n';
}
