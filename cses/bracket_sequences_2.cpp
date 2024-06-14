// Bracket Sequences 2  -  https://cses.fi/problemset/task/2187/
//
// We can use a similar process to the easier version of this problem.
// If we rewrite the problem as grid traversal, where we aim to move from
// the point (0,0) to (n/2,n/2) and we can only move right '(' or up ')'
// without crossing the diagonal, there is a nice formula: (2n choose n) -
// (2n choose n-1). To extend this to a sequence with a prefix, we can
// treat the prefix instead as a postfix, and compute the number of ways to
// move from (0,0) to (a,b) where a and b represent the number of left and
// right parentheses in the final sequence *but not in the postfix*, and
// still ensure that no paths cross the diagonal. The formula for this is
// simply (a+b choose a) - (a+b choose a-1).

#include <iostream>
#include <string>

constexpr int m = 1e9 + 7;

// fast nck with binomial
int nck(int a, int b){
	// balance
	if(b+b > a) return nck(a, a-b);

	long long num = 1, den = 1;

	// factorial-like setup
	for(int i=b; i; --i)
		num = num*(a-i+1) % m, den = den*i % m;

	// bin exp
	for(int x = m-2; x; x /= 2){
		if(x&1) num = num*den % m;
		den = den*den % m;
	}

	return (int)num;
}

int main(){
	int n; std::cin >> n;

	std::string s; std::cin >> s;

	// if odd n, answer must be 0
	if(n&1){
		std::cout << "0\n";
		return 0;
	}

	n /= 2;

	// r, d = # of right and up moves remaining
	int r = n, u = n, height = 0;

	// iterate over characters and process
	for(char c : s){
		// keep track of "height" above the diagonal
		if(c == '(') --r, ++height;
		else --u, --height;

		// check if any conditions violated
		// - if crossed diagonal, height is negative
		// - if used too many left or right paren, r/u will be negative
		if(height < 0 || r < 0 || u < 0){
			std::cout << "0\n";
			return 0;
		}
	}

	// compute answer and modulo to positive value
	int ret = nck(r+u, r);
	if(r) ret -= nck(r+u, r-1);
	if(ret < 0) ret += m;

	std::cout << ret << '\n';
}
