// Divisor Analysis  -  https://cses.fi/problemset/task/2182/
//
// Essentially just mod bash

#include <iostream>

using LL = long long;

constexpr LL M = 1e9 + 7, I = M - 1;

int main(){
	int n; std::cin >> n;

	LL num = 1, sum = 1, prod = 1, pre = 1;

	for(int i=0; i<n; ++i){
		int p, e; std::cin >> p >> e;

		// accumulating count of divisors is very easy

		num = num * (e+1) % M;

		// sum of divisors is product of (1 + p + p^2 +
		// p^3 + ... + p^e) across all cases - similar
		// to normal binary exp, but compute (1), (1+p),
		// (1+p+p^2+p^3), etc. and sum instead of prod

		LL p2 = 1, p3 = p, part = 0;
		for(int j=e; j; j >>= 1){
			if(j&1) part = (p2 + part * p3 % M) % M;

			p2 = (p2 + p2 * p3 % M) % M;
			p3 = p3 * p3 % M;
		}

		sum = sum * (1 + p * part % M) % M;

		// product of divisors is kinda silly but I did it
		// by basically noticing that any time a new factor
		// group is added, it contributes (1+e) possible new
		// parts to each existing factor: 1, p, p^2, ... , p^e
		// and this essentially raises the previous [prod] to
		// the power of (e^1).

		part = 1, p2 = prod;
		for(int j=e+1; j; j >>= 1){
			if(j&1) part = part * p2 % M;
			p2 = p2 * p2 % M;
		}

		prod = part;

		// then we need to compute the amount of [p] that is
		// multiplied in, and this is just the number of previous
		// factors [pre] multiplied by the number of times [p]
		// exists by itself - in p * p^2, there is 3. we calculate
		// with (e)(e+1)/2.

		p2 = 1, p3 = p;

		for(LL j=((LL)e*e+e)/2; j; j >>= 1){
			if(j&1) p2 = p2 * p3 % M;
			p3 = p3 * p3 % M;
		}

		for(int j=pre; j; j >>= 1){
			if(j&1) prod = prod * p2 % M;
			p2 = p2 * p2 % M;
		}

		// because of mods - pre needs to mod against M-1, which
		// is precomputed as I

		pre = pre * (e+1) % I;
	}

	std::cout << num << ' ' << sum << ' ' << prod << '\n';
}
