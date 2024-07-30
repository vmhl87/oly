// A guaranteed optimal strategy is essentially to teleport to the oldest
// portal necessary to reach all ancestors, and then sometimes use the
// portals again to skip forward in time over blocks of 12 years that
// don't have any ancestors in them. We only have k jumps total, so we
// can only skip over k-1 ranges of time. Essentially, find the sizes of
// all empty blocks, and choose the k-1 largest.

#include <algorithm>
#include <iostream>

int anc[70000], gaps[70000];

int main(){
	int n, k; std::cin >> n >> k, anc[n] = 13;
	for(int i=0; i<n; ++i) std::cin >> anc[i], anc[i] *= -1;
	std::sort(anc, anc+n+1);

	for(int i=1; i<=n; ++i)
		gaps[i-1] = std::max(0, (anc[i]/12) - (anc[i-1]/12) - 1);

	std::sort(gaps, gaps+n);

	int rem = 0;
	for(int i=1; i<k; ++i) rem += gaps[n-i];

	std::cout << 12 * ((anc[n]/12) - (anc[0]/12) - rem) << '\n';
}
