// Stick Lengths  -  https://cses.fi/problemset/task/1074/
// If we sort the stick lengths, there is an O(1) procedure to, given
// the cost to center around stick length i, compute the cost to center
// around stick length i+1.

#include <algorithm>
#include <iostream>

int main(){
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int n; std::cin >> n;
	long long s[n];
	for(int i=0; i<n; ++i) std::cin >> s[i];
	std::sort(s, s+n);
	// initially center around first element
	long long sum = 0;
	for(int i=1; i<n; ++i) sum += s[i] - s[0];
	// store running best
	long long best = sum;
	// transform:
	for(int i=1; i<n; ++i){
		// say that our sorted list of lengths is 1, 2, 2, 3, 5 and we
		// previously were centered around the 1, and now are around the
		// first 2. currently, i=1.
		// We can observe that the cost of the first stick increases by 1,
		// and all of the other costs decrease by 1. As a generic formula,
		// when going from centered around (i-1) to centered around i, then
		// the cost of the first i sticks increases by s[i] - s[i-1], and the
		// other (n-i) sticks' cost decreases by s[i] - s[i-1].
		// Condenses into the following expression.
		sum -= (s[i] - s[i-1]) * (n-i-i);
		// update running best
		best = sum < best ? sum : best;
	}
	std::cout << best << '\n';
}
