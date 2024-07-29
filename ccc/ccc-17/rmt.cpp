#include <iostream>
#include <vector>
#include <array>

using LL = long long;
const int MAXN = 150000;

// split station into sqrtn buckets, store sum of each here
LL bucket[600];

// station ctl
int group[MAXN], at[MAXN], pos[MAXN], shift[MAXN];

// train line ctl
std::vector<std::array<int, 2>> add[MAXN], del[MAXN];
std::vector<int> line[MAXN];

// don't actually shift values, too slow
int get(int i){
	int p = (pos[i] + shift[group[i]]) % line[group[i]].size();
	return at[line[group[i]][p]];
}

int main(){
	int n, m, q; std::cin >> n >> m >> q;
	for(int i=0; i<n; ++i) std::cin >> group[i], --group[i];
	for(int i=0; i<n; ++i) std::cin >> at[i];

	// build buckets
		// int rn = 0; while(rn*rn < n) ++rn;
	int rn = 256; // optimal bucket size seems to be 256
	for(int i=0; i<n; ++i) bucket[i/rn] += at[i];

	// compute each station's position in its train line
	for(int i=0; i<n; ++i)
		pos[i] = line[group[i]].size(), line[group[i]].push_back(i);

	// and determine the bucket shifts per line
	for(int i=0; i<m; ++i)
		for(int j=0; j<line[i].size(); ++j){
			int a = line[i][j?j-1:line[i].size()-1], b = line[i][j];

			if(a/rn != b/rn){
				add[i].push_back({a, b/rn});
				del[i].push_back({a, a/rn});
			}
		}

	while(q--){
		int t; std::cin >> t;
		
		if(t&1){
			int l, r; std::cin >> l >> r, --l, --r;

			// basically just sum up all intermediate buckets +
			// both ends

			LL res = 0;

			if(l/rn == r/rn) for(int i=l; i<=r; ++i) res += get(i);
			else{
				for(int i=l; i<rn*(1+l/rn); ++i) res += get(i);
				for(int i=1+l/rn; i<r/rn; ++i) res += bucket[i];
				for(int i=rn*(r/rn); i<=r; ++i) res += get(i);
			}

			std::cout << res << '\n';

		}else{
			int x; std::cin >> x, --x;

			// process bucket shifts

			for(const auto &[p, b] : add[x]) bucket[b] += get(p);
			for(const auto &[p, b] : del[x]) bucket[b] -= get(p);

			--shift[x]; if(shift[x] < 0) shift[x] += line[x].size();
		}
	}
}
