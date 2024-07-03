// subarray sums 2
// freq map bash - iterate over right bounds and find valid left

#include <iostream>
#include <map>

typedef long long LL;

int main(){
	int n, x; std::cin >> n >> x;

	LL p[n+1]; p[0] = 0;

	for(int i=0; i<n; ++i)
		std::cin >> p[i+1], p[i+1] += p[i];

	LL res = 0;
	std::map<long long, int> count;

	for(int i=0; i<=n; ++i)
		res += count[p[i]-x], ++count[p[i]];

	std::cout << res << '\n';
}
