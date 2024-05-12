// Subarray Divisibility  -  https://cses.fi/problemset/task/1662/
// We can simplify this problem much by using prefix sums. With a
// prefix sum array, we can compute the sum of an array in O(1).
// The trick we can use here is to store in the prefix array the
// prefix sum mod n, because then if two prefix sums are the same
// value mod n, their difference will be divisible by n, and the
// sum of the representative array will be divisible by n.
// So all we need to do is store a count of how many prefix sums
// are 0 mod n, 1 mod n, 2 mod n, etc. and then for each of those
// counts, find the number of pairs of prefix sums. (ex. if there
// are 3 sums that are 4 mod n, there are (3 choose 2) ways to
// pick two sums that are 4 mod n.)

#include <iostream>

int main(){
	// fastio
	std::cin.tie(0) -> sync_with_stdio(0);
	int n; std::cin >> n;
	// counts, sum
	long long c[n] = {0}, sum = 0;
	// the first (zeroth) prefix sum is the zero one
	c[0] = 1;
	// iterate
	for(int i=0; i<n; ++i){
		int x; std::cin >> x;
		// update sum mod n
		sum = (sum + x) % n;
		if(sum < 0) sum += n;
		// increment count
		++c[sum];
	}
	long long ret = 0;
	// if n values, (n * (n-1))/2 ways to pick 2
	for(long long x : c) ret += (x * (x-1))>>1;
	std::cout << ret << '\n';
}
