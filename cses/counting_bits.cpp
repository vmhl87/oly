// Counting Bits  -  https://cses.fi/problemset/task/1146/
// We can perform an O(log n) algorithm by iterating over the
// bits of N and determining how many of the numbers 1 through N
// have that bit set; there is a nice pattern to it

#include <iostream>

int main(){
	long long n, ret = 0; std::cin >> n;

	for(long long m = n+1, p = 1, d = 0; m; p<<=1, m>>=1){
		ret += m/2 * p;
		if(n&p) ret += d;
		if(m&1) d += p;
	}

	std::cout << n << '\n';
}
