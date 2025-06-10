#include <iostream>

bool sieve[(int)1e6];

int main(){
	int sum = 0;
	for(int i=0; i<200; ++i){
		if(i%3) sum += i*i;
		else sum -= i*i;
	}
	std::cout << sum << '\n';
	for(int i=0; i<1e6; ++i) sieve[i] = 1;

	for(int i=2; i<1e6; ++i) if(sieve[i]){
		for(int j=i+i; j<1e6; j+=i) sieve[j] = 0;
	}

	int res = 0;

	for(int i=2; i<sum; ++i){
		if(sieve[i] && sum%i == 0){
			std::cout << i << '\n';
			res += i;
		}
	}

	std::cout << res << '\n';
}
