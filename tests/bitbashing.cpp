#include <iostream>

int main(){
	int n, k; std::cin >> n >> k;

	int last = 0;

	for(int i=0; i<=n; ++i)
		if(__builtin_popcount(i) == k){
			int j = i;
			while(j) std::cout << "_1"[j&1], j >>= 1;
			std::cout << ' ' << i << ' ' << i-last << '\n';
			last = i;
		}
}
