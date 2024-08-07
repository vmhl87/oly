// idea: some sort of state machine
//
//  - track longest AIS with last 2 elements strictly increasing
//  - track longest AIS without such restriction
//
// then use state machine to propagate

#include <algorithm>
#include <iostream>
#include <vector>
#include <array>
#include <set>

int a[200000], lo[200000], hi[200000],
	lodepth[200000], hidepth[200000];

int main(){
	int n, q; std::cin >> n >> q;
	for(int i=0; i<n; ++i) std::cin >> a[i];

	std::vector<std::array<int, 2>> lis;
	std::set<std::array<int, 2>> lazy;

	for(int i=0; i<n; ++i){
		std::array<int, 2> cmp = {a[i], -1};
		auto x = std::upper_bound(lis.begin(), lis.end(), cmp);
		if(x == lis.end()) lo[i] = lis.size() ? lis.back()[1] : -1,
			lis.push_back({a[i], i});
		else{
			(*x) = {a[i], i};
			if(x != lis.begin()) --x, lo[i] = (*x)[1];
			else lo[i] = -1;
		}

		lodepth[i] = lo[i] == -1 ? 0 : hidepth[lo[i]] + 1;

		if(lazy.size()) hi[i] = -(*lazy.begin())[1];
		else hi[i] = -1;

		hidepth[i] = std::max(lodepth[i], hi[i] == -1 ? 0 : lodepth[hi[i]] + 1);

		lazy.insert({-lodepth[i], -i});
	}

	for(int i=0; i<n; ++i) std::cout << i << "->" << lo[i] << "->" << hi[i] << "\n d: " << lodepth[i] << ',' << hidepth[i] << '\n';
}
