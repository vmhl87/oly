#include <iostream>
#include <array>
#include <set>

using ll = long long;

std::set<std::array<int, 2>> g1, g2;

int perm[8], rev[8], used[8];
int cost[8][8];
int n;

ll best;

void permute(int i){
	if(i==n){
		for(int j=0; j<n; ++j)
			rev[perm[j]] = j;

		ll res = 0;

		for(const auto &[a, b] : g2){
			if(!g1.count({perm[a], perm[b]}) && !g1.count({perm[b], perm[a]})){
				if(a<b) res += cost[a][b];
				else res += cost[b][a];
			}
		}

		for(const auto &[a, b] : g1){
			if(!g2.count({rev[a], rev[b]}) && !g2.count({rev[b], rev[a]})){
				if(rev[a]<rev[b]) res += cost[rev[a]][rev[b]];
				else res += cost[rev[b]][rev[a]];
			}
		}

		if(res < best) best = res;
	}else{
		for(int j=0; j<n; ++j) if(!used[j]){
			used[j] = 1;
			perm[i] = j;
			permute(i+1);
			used[j] = 0;
		}
	}
}

int main(){
	std::cin >> n;

	int m1; std::cin >> m1;
	while(m1--){
		int a, b; std::cin >> a >> b;
		g1.insert({a-1, b-1});
	}

	int m2; std::cin >> m2;
	while(m2--){
		int a, b; std::cin >> a >> b;
		g2.insert({a-1, b-1});
	}

	for(int i=0; i<n; ++i)
		for(int j=i+1; j<n; ++j)
			std::cin >> cost[i][j],
				best += cost[i][j];

	permute(0);

	std::cout << best << '\n';
}
