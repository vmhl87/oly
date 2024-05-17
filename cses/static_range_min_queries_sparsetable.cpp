// Static Range Minimum Queries  -  https://cses.fi/problemset/task/1647/
// Using a sparse table, each query can be computed in O(1), with O(nlogn)
// precomputation time.

#include <iostream>
#include <cmath>

// static allocation is faster
int table[26][200000];

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	// input everything
	int n, q, b; std::cin >> n >> q, b = 31 - __builtin_clz(n);
	for(int i=0; i<n; ++i) std::cin >> table[0][i];

	// build sparse table
	for(int i=1; i<=b; ++i)
		for(int j=0; j + (1<<i) <= n; ++j)
			table[i][j] = std::min(table[i-1][j], table[i-1][j + (1<<(i-1))]);

	while(q--){
		int l, r; std::cin >> l >> r, --l, --r;

		// each query can be decomposed into two overlapping segments
		int w = 31 - __builtin_clz(r - l + 1);
		std::cout << std::min(table[w][l], table[w][r - (1<<w) + 1]) << '\n';
	}
}
