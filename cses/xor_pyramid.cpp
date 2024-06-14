// Xor Pyramid  -  https://cses.fi/problemset/task/2419/
//
// Several observations greatly simplify the problem:
// 
// 1. Xor is an associative operation, meaning (a ^ b) ^ c == a ^ ( b ^ c),
//    so rather than computing each layer one after another, we can instead
//    count the number of times each individual number in the bottom row is
//    xor'ed into the final number.
//
// 2. The number of ways that some number in some row is xor'ed into the final
//    value is equal to the number of paths from that number to the top, where
//    paths must only move up and to the left or up and to the right. This is
//    computable by pascal's triangle, or binomial coefficients.
//
// 3. If a number is xor'ed an even number of times, it makes no difference
//    in the final value. If it is xor'ed an odd number of times, it is
//    equivalent to xor'ing it only once.
//
// So, we essentially need to compute the parity (even/oddness) of the binomial
// coefficients (n-1 choose 0), (n-1 choose 1), (n-1 choose 2), etc., and xor
// the values of the bottom row only if their binomial coefficients are odd.
//
// Computing binomial coefficients can be done in many ways. Here, we will use
// this factorial version:
// 
//    n choose k = n! / (k! (n-k)!)
//
// Computing factorials is tricky because we often exceed the integer limit.
// However, we don't actually need the value of the factorial - we only need
// the parity of the entire expression.
//
// We do this by keeping track not of the value of the (n choose k) but the
// power of two in its value. (The power of 2 in 48, for example, is 4, because
// 2^4 = 16 and the biggest power of 2 in 48 is 16.)
//
// If the power of two is nonzero, the whole value is even. Otherwise, it is
// odd. To go from (n choose k) to (n choose k+1), the numerator does not
// change. The denominator multiplies by (k+1) from the k! term, and divides
// by (n-k) from the (n-k)! term.
//
// We update the overall power of two by adding the power of two in (n-k) and
// subtracting the power of two in (k+1).

#include <iostream>

int main(){
	int n; std::cin >> n;

	int res = 0;

	// overall power of two - starts at 0 because (n-1 choose 0) = 1
	int twos = 0;

	// loop through all values of k
	for(int k=0; k<n; ++k){
		// input bottom row value, and xor into the result if (n-1 choose k)
		// is odd
		int a; std::cin >> a;
		if(!twos) res ^= a;

		// update overall power of 2
		twos += __builtin_ctz(n-1-k) - __builtin_ctz(k+1);
	}

	std::cout << res << '\n';
}
