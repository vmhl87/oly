// Nearest Smallest Values
//
// So, we can use monotonic stack for this -
// however there is a faster way: if we know
// for all elements [0, i-1] their nearest
// smallest element, we can compute i's result
// by just starting at [i-1] and continuously
// moving to [i-1]'s nearest smallest, etc.
// until we arrive at an element smaller than
// element i; effectively, we simulate the
// stack without actually storing it anywhere
//
// very fast; 0.05ms runtime on cses with
// fastio and 0.15ms without

#include <iostream>

int out[200001], val[200001];

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int n; std::cin >> n;

	for(int i=0; i<n; ++i){
		std::cin >> val[i+1], out[i+1] = i;

		while(val[out[i+1]] >= val[i+1])
			out[i+1] = out[out[i+1]];

		std::cout << out[i+1] << " \n"[i==n-1];
	}
}
