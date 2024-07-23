// I couldn't find a very good solution in contest,
// so I just moved on - but scraped a couple partials
// with a constructive DP approach: compute for each
// 1 <= i <= n by iterating over all k

#include <iostream>

int out[1000001];

int main(){
	int n; std::cin >> n;

	out[1] = 1;

	for(int i=2; i<=n; ++i){
		// n^2 did not get too far so to steal 2 more
		// partials I used sqrt decomposition - this is
		// actually very similar to the CSES problem
		// "counting divisors" which I did recently
		for(int k=1; k*k<=i; ++k){
			if(k-1) out[i] += out[i/k];
			int l = std::max(k, i/(k+1)), r = i/k;
			out[i] += out[k] * (r - l);
		}
	}

	// 7 points partials :clown:
	std::cout << out[n] << '\n';
}
