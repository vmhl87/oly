// Counting Divisors  -  https://cses.fi/problemset/task/1713/
// Essentially just application of a simple sqrt algorithm to
// determine the powers of each prime factor, and then compute
// the product of each of them plus one

#include <iostream>

void test_case(){
	int n; std::cin >> n;

	// We'll draw off each prime factor individually, and
	// combine it into the final result as we are doing so.
	// This avoids using a ds such as an std::map.
	long long res = 1;

	// This is the pseudo-sqrt algorithm: count up and remove
	// factors of n as we go
	for(int i = 2; i*i <= n; ++i){
		// Determine the power on the fly - this has the
		// benefit of also ensuring that any i we find will
		// be guaranteed to be prime, and also makes the
		// algorithm slightly faster as n, and the upper
		// bound for i, decreases
		int power = 0;
		while(n%i == 0) ++power, n /= i;

		res *= ++power;
	}

	// It is possible that a singular prime factor is not
	// fully removed from n. For example, when decomposing
	// n = 14, the 7 will not be removed, because 7 > sqrt(14).
	if(n > 1) res *= 2;

	std::cout << res << '\n';
}

int main(){
	int t; std::cin >> t;

	while(t--) test_case();
}
