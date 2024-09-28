#include <iostream>
#include <vector>

using ll = long long;

ll score[3001][3001];
bool vis[3001][3001];

ll of(int i, int k, int c, int v, int x){
	ll d = (k-x)/c;
	return score[i][x] + d*v - d*d;
}

int main(){
	int n, w; std::cin >> n >> w;

	vis[0][0] = 1;

	for(int i=0; i<n; ++i){
		int c, v; std::cin >> c >> v;

		for(int j=0; j<c; ++j){
			std::vector<int> starts;
			int idx = 0;

			for(int k=j; k<=w; k+=c){
				if(vis[i][k]){
					starts.push_back(k);
					if(score[i][k] >= of(i, k, c, v, starts[idx]))
						idx = starts.size() - 1;
				}

				if(starts.size()){
					vis[i+1][k] = 1;

					while(idx < starts.size()-1 &&
							of(i, k, c, v, starts[idx]) <= of(i, k, c, v, starts[idx+1]))
						++idx;

					score[i+1][k] = of(i, k, c, v, starts[idx]);
				}
			}
		}
	}

	for(int i=0; i<=n; ++i)
		for(int j=0; j<=w; ++j)
			std::cout << score[i][j] << " \n"[j==w];

	ll res = 0;
	for(int i=0; i<=w; ++i) res = std::max(res, score[n][i]);
	std::cout << res << '\n';
}
