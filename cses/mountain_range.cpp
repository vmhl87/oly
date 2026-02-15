// keep track of biggest to the left, biggest to the right
// then sort in increasing order of height, and find for
// each mountain the mountain in range with highest
// reachability (1 rmq); finally run global rmq

#include <iostream>
#include <cassert>
#include <array>
#include <map>

const int N = 2e5;

std::array<int, 2> t[N*2];
int a[N], n;

std::array<int, 2> rmq(int l, int r){
	std::array<int, 2> res = {0, -1};

	for(l+=n, r+=n; l < r; l/=2, r/=2){
		if(l&1) res = std::max(res, t[l++]);
		if(r&1) res = std::max(res, t[--r]);
	}

	return res;
}

int best = 0;

void dfs(int l, int r, int d){
	best = std::max(best, d);
	auto [v, i] = rmq(l, r);

	if(a[l] == v) ++l;
	if(a[r-1] == v) --r;

	if(l < i) dfs(l, i, d+1);
	if(i+1 < r) dfs(i+1, r, d+1);
}

int main(){
	std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> a[i], t[i+n] = {a[i], i};
	for(int i=n-1; i; --i) t[i] = std::max(t[i*2], t[i*2+1]);

	std::map<int, int> m;

	for(int i=0; i<n; ++i){
		dfs(m[a[i]], i+1, 1);
		m[a[i]] = i;
	}

	std::cout << best << '\n';
}
