#include <iostream>
#include <map>

using ll = long long;
const int M = 1e9 + 7;

ll res = 0;
int n, m;

std::map<int, int> prime;

int main(){
	std::cin >> n >> m;

	// find all divisors of n
	// then process each one (using parity of # of divisors)
	
	for(int i=2; i*i<=n; ++i)
		while(n%i == 0) ++prime[i], n /= i;

	if(n>1) ++prime[n];

	for(const auto &[i, c] : prime)
		std::cout << i << ": " << c << '\n';

	std::cout << res << '\n';
}
