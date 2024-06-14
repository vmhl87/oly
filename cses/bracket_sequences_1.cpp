// Bracket Sequences  -  https://cses.fi/problemset/task/2064/
// For some very cool mathematical reasons, the answer is always
// equal to the (n/2)th catalan number

#include <iostream>

int main(){
	int n; std::cin >> n;

	// process if odd
	if(n&1){
		std::cout << "0\n";
		return 0;
	}

	n /= 2;

	// nth catalan number = (2n choose n) / (n+1)
	
	// numerator, denominator
	long long num = 1, den = n+1;

	constexpr int m = 1e9 + 7;

	// factorial type thing
	for(int i=n; i; --i){
		num = num*(i+n) % m;
		den = den*i % m;
	}

	// invert denominator and multiply to numerator
	for(int m2 = m-2; m2; m2 >>= 1){
		if(m2&1) num = num*den % m;
		den = den*den % m;
	}

	std::cout << num << '\n';
}
