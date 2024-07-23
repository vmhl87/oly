#include <iostream>
#include <vector>
#include <array>

using LL = long long;

LL lst[150000], rst[150000];
int group[150000], at[150000], shift[150000], pos[150000];
std::vector<LL> line[150000];

LL _range(int i, int l, int r){
	return line[i][r+1] - line[i][l];
}

LL range(int i, int l, int r){
	l += shift[i], r += shift[i];
	l %= line[i].size()-1, r %= line[i].size()-1;

	if(l > r) return _range(i, 0, r) + _range(i, l, line[i].size()-1);

	return _range(i, l, r);
}

int main(){
	int n, m, q; std::cin >> n >> m >> q;
	for(int i=0; i<n; ++i) std::cin >> group[i], --group[i];
	for(int i=0; i<n; ++i) std::cin >> at[i];

	for(int i=0; i<n; ++i){
		if(!line[group[i]].size()) line[group[i]].push_back(0);
		line[group[i]].push_back(line[group[i]].back()+at[i]);
		pos[i] = line[group[i]].size() - 1;
	}

	for(int i=0; i<n; ++i) if(i){
		lst[i] = lst[i-1];
		if(pos[i-1] == line[group[i-1]].size()-1) lst[i] += line[group[i-1]].back();
	}

	for(int i=0; i<n; ++i) if(i){
		rst[i] = rst[i-1];
		if(pos[n-i] == 1) rst[i] += line[group[n-i]].back();
	}

	LL all = 0;
	for(int i=0; i<n; ++i) all += at[i];

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
