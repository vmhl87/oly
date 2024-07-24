#include <iostream>
#include <vector>
#include <array>

using LL = long long;

const int MAXN = 150000;

LL bucket[400];
int group[MAXN], at[MAXN], pos[MAXN];
std::vector<int> line[MAXN];

int main(){
	int n, m, q; std::cin >> n >> m >> q;
	for(int i=0; i<n; ++i) std::cin >> group[i], --group[i];
	for(int i=0; i<n; ++i) std::cin >> at[i];

	int rn = 0; while(rn*rn < n) ++rn;
	for(int i=0; i<n; ++i) bucket[i/rn] += at[i];

	for(int i=0; i<n; ++i){
		line[group[i]].push_back(line[group[i]].back()+at[i]);
		pos[i] = line[group[i]].size() - 1;
	}

	while(q--){
		int t; std::cin >> t;
		
		if(t&1){
			int l, r; std::cin >> l >> r, --l, --r;

			LL res = all;

			if(l) res -= lst[l-1], res -= range(group[l], 0, pos[l]-2);
			if(r < n-1) res -= rst[n-2-r], res -= range(group[r], pos[r], line[group[r]].size()-2);

			std::cout << res << '\n';

		}else{
			int x; std::cin >> x, --x, --shift[x];
			if(shift[x] < 0) shift[x] += line[x].size()-1;
		}
	}
}
