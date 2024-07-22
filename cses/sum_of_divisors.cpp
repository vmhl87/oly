#include <iostream>

using LL = long long;

constexpr LL M = 1e9 + 7;

int main(){
	LL n; std::cin >> n;

	LL res = 0;

	for(LL f = 1; f*f <= n; ++f){
		res = (res + f * (n / f) % M) % M;

		LL a = std::max(f, n/(f+1) % M), b = n/f % M,
		   all = (b*b+b-a*a-a)/2 % M;
		res = (res + f * all % M) % M;
	}

	std::cout << res << '\n';
}
