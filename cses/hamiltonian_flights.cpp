#include <algorithm>
#include <iostream>

using ll = long long;
constexpr int MOD = 1e9 + 7;

int adj[20][20];
ll way[1<<20][20];
int n;

int order[1<<20];

bool cmp(int i, int j){
	return __builtin_popcount(i) < __builtin_popcount(j);
}

int main(){
	int m; std::cin >> n >> m;
	while(m--){
		int a, b; std::cin >> a >> b;
		++adj[a-1][b-1];
	}

	for(int i=0; i<1<<n; ++i) order[i] = i;
	std::sort(order, order+(1<<n), cmp);

	way[1][0] = 1;

	for(int i=1; i<1<<n; ++i){
		int j = order[i];
		for(int k=0; k<n; ++k) if(j&(1<<k)){
			if(k==0 && j==1) continue;
			ll res = 0;
			for(int x=0; x<n; ++x) if(j&(1<<x))
				res += adj[x][k]*way[j^(1<<k)][x];
			way[j][k] = res % MOD;
		}
	}

	std::cout << way[(1<<n)-1][n-1] << '\n';
}
