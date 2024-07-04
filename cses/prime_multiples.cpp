// Prime Multiples  -  https://cses.fi/problemset/task/2185/
//
// PIE bash!
// We can do the standard sort of bitwise bash and iterate
// over all possible combinations of primes, and either add
// or subtract the number of values in [1, n] divisible
// by said product depending on the number of primes.
//
// I somehow read the bounds and reasoned that 2^20 would
// be too slow (I read it as 10^20) so I made some weird filter
// recursive thing that prunes out products of primes if they
// get too large, which really wasn't necessary lol

#include <iostream>

typedef long long LL;

LL res = 0, n, a[20];
int k;

// current parity (flips when add new prime), use flag
// (only multiply in if prime was just added to permutation),
// previous product, index in a[]
void pie(int par, int use, LL prev, int i){
	if(use) res +=  par * (n / prev);

	if(i == k) return;

	// we can always just not add the current prime
	pie(par, 0, prev, i+1);

	// only add current prime if does not overflow past n
	if(n / prev >= a[i])
		pie(-par, 1, prev*a[i], i+1);
}

int main(){
	std::cin >> n >> k;
	for(int i=0; i<k; ++i) std::cin >> a[i];

	// parity initially starts as -1 because parity of single
	// primes should be 1
	pie(-1, 0, 1ll, 0);

	std::cout << res << '\n';
}
