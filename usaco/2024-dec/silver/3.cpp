#include <iostream>
#include <vector>
#include <array>
#include <queue>

const int N = 1002, M = 1e6;

std::vector<std::array<int, 2>> adj[N*N];
bool v[N][N], V[N*N];
int t[N*N], T;

int p[M+1];

int main(){
	int n, q; std::cin >> n >> q;

	/*
	for(int i=0; i<n+2; ++i)
		for(int j=0; j<n+2; ++j)
			t[i*N+j] = -1;
	*/

	while(q--){
		int x, y; char c;
		std::cin >> x >> y >> c;

		//t[x*N+y] = T++;
		v[x][y] = 1;

		int i = x*N+y;

		if(c == 'L') --y;
		if(c == 'R') ++y;
		if(c == 'U') --x;
		if(c == 'D') ++x;

		int j = x*N+y;

		//adj[i].push_back({j, M});
		adj[j].push_back({i, M});

		/*
		if(x-1 != j) adj[i].push_back({x-1, T});
		if(x+1 != j) adj[i].push_back({x+1, T});
		if(x-N != j) adj[i].push_back({x-N, T});
		if(x+N != j) adj[i].push_back({x+N, T});
		*/
		if(i-1 != j) adj[i-1].push_back({i, T});
		if(i+1 != j) adj[i+1].push_back({i, T});
		if(i-N != j) adj[i-N].push_back({i, T});
		if(i+N != j) adj[i+N].push_back({i, T});

		++T;
	}

	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j)
			if(!v[i][j]){
				int x = i*N+j;
				/*
				adj[x].push_back({x-1, M});
				adj[x].push_back({x+1, M});
				adj[x].push_back({x-N, M});
				adj[x].push_back({x+N, M});
				*/
				adj[x-1].push_back({x, M});
				adj[x+1].push_back({x, M});
				adj[x-N].push_back({x, M});
				adj[x+N].push_back({x, M});
			}

	/*
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=n; ++j){
			//int res = 0;

			for(int i=0; i<N*N; ++i)
				V[i] = 0;

			std::priority_queue<std::array<int, 2>> Q;
			Q.push({M, i*N+j});

			while(Q.size()){
				int j = Q.top()[0],
					i = Q.top()[1];
				Q.pop();

				if(V[i]) continue;
				V[i] = 1;

				if(!adj[i].size()){
					//res = j;
					++p[j];
					break;
				}

				for(const auto &[x, c] : adj[i])
					Q.push({std::min(j, c), x});
			}

			//std::cout << res << " \n"[j==n];
		}
	*/

	std::priority_queue<std::array<int, 2>> Q;

	for(int i=0; i<N*N; ++i) if(adj[i].size() == 1)
		Q.push({M, i});

	while(Q.size()){
		int j = Q.top()[0],
			i = Q.top()[1];
		Q.pop();

		if(V[i]) continue;
		V[i] = 1;

		++p[j];

		for(const auto &[x, c] : adj[i])
			Q.push({std::min(j, c), x});
	}

	int P = 0;

	for(int i=0; i<T; ++i){
		P += p[i];
		std::cout << P << '\n';
	}
}
