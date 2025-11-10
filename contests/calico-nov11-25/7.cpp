#include <iostream>
#include <cmath>

double a[(size_t) 1e4];

int main(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> a[i];

	// limited to 99 avg per thing
	
	int total = 0, gap = 0;
	
	for(int i=0; i<n; ++i){
		if(a[i] >= 0.5) ++gap;
		else total += std::ceil(std::log(0.1) / std::log(1.0 - 2.0*a[i]));
		++gap;
	}

	double factor = 1.0, max = 1e6;
	if(total > max-gap)
		factor = ((double)max-gap-10) / ((double)total);

	for(int i=0; i<n; ++i){
		if(a[i] >= 0.5) std::cout << "REACT\n";
		else{
			int v = std::ceil(std::log(0.1) / std::log(1.0 - 2.0*a[i]));
			int w = std::floor(((double)v) * factor);
			for(int j=0; j<w; ++j) std::cout << "REACT\n";
		}

		std::cout << "NEXT\n";
	}
}

/*
#include <iostream>
#include <cmath>

int main(){
	double p; std::cin >> p;

	double P = 0.5;

	for(int i=1; i<100; ++i){
		// P = P*(1.0-p) + (1.0-P)*p;
		// P = 0.5 - ((0.5-P)*(1.0-p) + (0.5+P)*p);
		// P = P - P*2*p;
		P *= (1.0 - 2.0 * p);
		// dP/dt = -2p * P
		// -1/2pP dP = dt
		// -1/2p ln P = t
		// ln P = -2pt
		// P = e^-2pt
		std::cout << "iter " << i << ": " << 0.5-P << '\n';
		std::cout << "alt "
			<< 0.5 - std::pow(1.0 - 2.0*p, i)/2.0 << '\n';
	}
}

// [P  ] * [1-p   p]
// [1-P]   [p   1-p]
*/
