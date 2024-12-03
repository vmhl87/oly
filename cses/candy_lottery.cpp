#include <iostream>
#include <iomanip>
#include <math.h>

using ld = long double;

int main(){
	int n, k; std::cin >> n >> k;

	ld res = 0, last = 0;

	for(ld i=1; i<=k; ++i){
		ld x = pow(i/k, n);
		res += i * (x-last);
		last = x;
	}

	res *= 1e6;

	ld fract = res - floor(res);

	if(fract < 0.5) res = floor(res);
	else if(fract > 0.5) res = ceil(res);
	else if(((int)floor(res)) & 1) res = ceil(res);
	else res = floor(res);

	std::cout << std::fixed << std::setprecision(6) << res/1e6 << '\n';
}
