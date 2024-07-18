// So it turns out I fail to see obvious greedies

#include <iostream>
#include <vector>
#include <array>

using LL = long long;

int out[1000001];

int main(){
	LL n, m, k; std::cin >> n >> m >> k;

	int free = m;

	out[0] = 1, k -= n;

	int l = 0;
	for(int r=1; r<n; ++r){
		if(k < 0){
			std::cout << "-1\n";
			return 0;
		}

		LL best = r - l;

		if(best <= k){
			if(free > 1){
				out[r] = free, --free;
				k -= best;
			}else{
				k -= best-1;
				out[r] = out[l];
				++l;
			}
		}else{
			int p = r - k - 1; k = 0;
			out[r] = out[p];
		}
	}

	if(k){
		std::cout << "-1\n";
		return 0;
	}

	for(int i=0; i<n; ++i) std::cout << out[i] << " \n"[i==n-1];
}
