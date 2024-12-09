#include <iostream>
#include <iomanip>
#include <math.h>

using ld = long double;

int a[100];

ld r(int a, int b){
	if(a > b) return 1;
	return (ld)(a-1) / (ld)b;
}

ld f(int a, int b){
	ld res = 0;

	for(int i=1; i<=a; ++i)
		res += r(i, b);

	return res / a;
}

int main(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> a[i];
	
	ld res = 0;

	for(int i=0; i<n; ++i)
		for(int j=i+1; j<n; ++j)
			res += f(a[i], a[j]);

	res *= 1e6;

	ld fract = res - floor(res);

	if(fract < 0.5) res = floor(res);
	else if(fract > 0.5) res = ceil(res);
	else if(((int)floor(res)) & 1) res = ceil(res);
	else res = floor(res);

	std::cout << std::fixed << std::setprecision(6) << res/1e6 << '\n';
}
