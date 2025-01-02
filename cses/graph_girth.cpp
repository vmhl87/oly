#include <iostream>
#include <vector>
#include <queue>

const int N = 2500;

std::vector<int> adj[N];
int d[N];

int main(){
	int n, m; std::cin >> n >> m;
	
	while(m--){
		int a, b; std::cin >> a >> b;
		adj[--a].push_back(--b);
		adj[b].push_back(a);
	}

	int res = 1e9;

	for(int i=0; i<n; ++i){
		std::fill(d, d+n, 0);
		d[i] = 1;

		std::queue<int> q; q.push(i);

		while(q.size()){
			int t = q.front(); q.pop();
			for(int x : adj[t]) if(!d[x])
				d[x] = d[t]+1, q.push(x);
			else if(d[t] <= d[x])
				res = std::min(res, d[t]+d[x]-1);
		}
	}

	std::cout << (res == 1e9 ? -1 : res) << '\n';
}
