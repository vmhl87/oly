#include <iostream>
#include <vector>

const int maxn = 1e5;

int indeg[maxn], outdeg[maxn];
std::vector<int> adj[maxn];

int root[maxn];

int find(int i){
	if(root[i] < 0) return i;
	return root[i] = find(root[i]);
}

void merge(int a, int b){
	if((a = find(a)) == (b = find(b))) return;
	if(root[a] < root[b]) root[a] += root[b], root[b] = a;
	else root[b] += root[a], root[a] = b;
}

std::vector<int> part[maxn];
bool vis[maxn];

int main(){
	int n, m; std::cin >> n >> m;

	for(int i=0; i<n; ++i) root[i] = -1;

	while(m--){
		int a, b; std::cin >> a >> b;
		adj[--a].push_back(--b);
		++indeg[b], ++outdeg[a];
		merge(a, b);
	}

	for(int i=0; i<n; ++i) part[find(i)].push_back(i);

	int res = n;

	for(int i=0; i<n; ++i) if(part[i].size()){
		std::vector<int> s;
		--res;

		int comp = part[i].size();

		for(int x : part[i]) if(!indeg[x])
			s.push_back(x), vis[x] = 1;

		while(s.size()){
			int t = s.back(); s.pop_back();
			--comp;

			for(int x : adj[t]){
				--outdeg[t];
				if(!(--indeg[x]) && !vis[x])
					vis[x] = 1, s.push_back(x);
			}
		}

		if(comp) ++res;
	}

	std::cout << res << '\n';
}
