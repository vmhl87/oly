/* reasoning:
 *
 * Consider some subsequence [l..r] that violates the inequality,
 * i.e. max(a_l..a_r) < sum(a_l..a_r). Let the maximum value of this
 * sequence be at `m`. So, this means that a_m < sum(a_l..a_r), or in
 * other words, sum(a_l..a_m-1) + sum(a_m+1..a_r) is positive.
 *
 * Observe that if sum(a_l..a_m-1) + sum(a_m+1..a_r) is positive, at
 * least one of [l..m-1], [m+1..r] must have a positive sum. Then, the
 * sequence constructed by taking the positive sequence and adding `m`
 * will also violate the inequality.
 *
 * We can construct an algorithm to check this as so:
 *
 *    Pick the largest element of the input array, and divide it into
 *    two halves. If the left half has any positive suffix sums, or the
 *    right half has any positive prefix sums, report "NO".
 *
 *    Then, perform the same algorithm on each half. (divide and conquer)
 *
 * ~~The time complexity is n log n, similar to merge sort.~~
 *
 * ^ it turns out I forgot how d&c works. this approach can blow up to
 * quadratic time in worst-case (monotonically decreasing array)
 */

#include <iostream>

using ll = long long;
const int N = 2e5;

int a[N];

bool dnc(int l, int r){
	if(l == r) return 1;

	// find max & index
	int m = a[l], n = l;
	for(int i=l+1; i<r; ++i)
		if(a[i] > m) m = a[i], n = i;

	// check prefixes
	ll p = 0;
	for(int i=n-1; i>=l; --i){
		p += a[i];
		if(p > 0) return 0;
	}

	p = 0;
	for(int i=n+1; i<r; ++i){
		p += a[i];
		if(p > 0) return 0;
	}

	// divide
	return dnc(l, n) && dnc(n+1, r);
}

void test(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> a[i];

	std::cout << (dnc(0, n) ? "YES" : "NO") << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
