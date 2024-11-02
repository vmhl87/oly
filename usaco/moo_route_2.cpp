#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <array>

bool cmp(std::array<int, 3> a, std::array<int, 3> b){
	return a[1] > b[1];
}

struct node{
	std::vector<std::array<int, 3>> d;
	int a, best = -1, p = 0;
	bool in = 0;
	void build(){
		std::sort(d.begin(), d.end(), cmp);
	}
	bool next(){
		if(p == d.size()) return 0;
		if(d[p][1] >= best+a) return 1;
		return 0;
	}
	std::array<int, 3> now(){
		return d[p++];
	}
};

node adj[200000];

bool improve(int n, int o){
	return o == -1 || n < o;
}

int main(){
	int n, m; std::cin >> n >> m;

	while(m--){
		int c, r, d, s; std::cin >> c >> r >> d >> s;
		adj[c-1].d.push_back({d-1, r, s});
	}

	for(int i=0; i<n; ++i) std::cin >> adj[i].a, adj[i].build();
	adj[0].best = -adj[0].a;

	std::queue<int> spfa; spfa.push(0);

	while(spfa.size()){
		int i = spfa.front(); spfa.pop(), adj[i].in = 0;

		while(adj[i].next()){
			auto [x, start, end] = adj[i].now();
			if(improve(end, adj[x].best)){
				adj[x].best = end;
				if(!adj[x].in) spfa.push(x), adj[x].in = 1;
			}
		}
	}

	adj[0].best = 0;
	for(int i=0; i<n; ++i) std::cout << adj[i].best << '\n';
}
