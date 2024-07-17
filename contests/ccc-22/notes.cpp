#include <iostream>

using LL = long long;

int out[1000001];

int main(){
	LL n, m, k; std::cin >> n >> m >> k;

	if(k < n){
		std::cout << "-1\n";
		return 0;
	}

	k -= n;

	if(m == 2){
		if(k >= n){
			std::cout << "-1\n";
			return 0;
		}

		int par = 0;
		for(int i=0; i<n; ++i){
			if(i && k) par ^= 1, --k;
			std::cout << par+1 << " \n"[i==n-1];
		}

		return 0;
	}

	LL curr = n, at = 0;
	int last = 1;

	while(k){
		while(curr*(curr-1) > k*2) --curr;
		k -= (curr*(curr-1))/2;
		for(int i=0; i<curr; ++i){
			if(at >= n){
				std::cout << "-1\n";
				return 0;
			}
			out[at++] = (last+i)%n;
		}
		last = out[at-1];
	}

	for(int i=0; i<n; ++i) std::cout << out[i] << " \n"[i==n-1];
}
