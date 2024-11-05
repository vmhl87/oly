#include <iostream>

using ll = long long;

bool sieve[1000000];
int x[100000];

int main(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> x[i];

	for(int i=2; i<1e6; ++i) sieve[i] = 1;
	for(int i=2; i<1e6; ++i) if(sieve[i])
		for(int j=i+i; j<1e6; j+=i) sieve[j] = 0;

	ll res = ((ll)n * (ll)(n-1))/2;

	// this doesn't actually work because of duplicates, rip
	
	for(int i=0; i<1e6; ++i) if(sieve[i]){
		int part = 0;
		for(int j=0; j<n; ++j) if(x[j]%i == 0)
			res -= part, ++part;
	}

	std::cout << res << '\n';
}
