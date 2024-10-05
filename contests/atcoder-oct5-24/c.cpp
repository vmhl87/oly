#include <iostream>

using ll = long long;

int k[20];

int main(){
	ll all = 0;
	int n; std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> k[i], all += k[i]; 

	ll best = all;

	for(int i=0; i<1<<n; ++i){
		ll part = 0;
		for(int j=0; j<n; ++j)
			if(i&(1<<j)) part += k[j];
		best = std::min(best, std::max(part, all-part));
	}

	std::cout << best << '\n';
}
