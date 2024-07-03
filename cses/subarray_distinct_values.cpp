// Subarray Distinct Values  -  https://cses.fi/problemset/task/2428/
// sliding window map/multiset bash

#include <iostream>
#include <map>

typedef long long LL;

int main(){
	int n, k; std::cin >> n >> k;

	// multiset count bad
	std::map<int, int> window;

	LL res = 0;

	int a[n]; for(int i=0; i<n; ++i) std::cin >> a[i];

	int p = 0;

	// mantain window such that # of distinct is always <= k
	for(int i=0; i<n; ++i){
		++window[a[i]];

		while(window.size() > k){
			--window[a[p]];
			if(window[a[p]] == 0)
				window.erase(a[p]);

			++p;
		}

		// # of subarrays is just distance betwee start end + 1
		res += (LL)i - (LL)p + 1ll;
	}

	std::cout << res << '\n';
}
