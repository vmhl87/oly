#include <algorithm>
#include <iostream>
#include <vector>

int anc[70000], gaps[70000];

int main(){
	int n, k; std::cin >> n >> k;
	for(int i=0; i<n; ++i) std::cin >> anc[i];
	std::sort(anc, anc+n);

	for(int i=1; i<n; ++i)
		gaps[i-1] = std::max(0, (anc[i]/12) - (anc[i-1]/12) - 1);

	std::sort(gaps, gaps+n-1);

	int rem = 0;
	for(int i=1; i<k; ++i) rem += gaps[n-1-i];

	std::cout << 12 * ((anc[n-1]/12) - (anc[0]/12) + 1 - rem) << '\n';
}
