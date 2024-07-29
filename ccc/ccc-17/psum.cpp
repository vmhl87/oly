#include <iostream>

int a[100000], b[100000];

int main(){
	int n; std::cin >> n;

	for(int i=0; i<n; ++i) std::cin >> a[i];
	for(int i=0; i<n; ++i) std::cin >> b[i];

	// accumulate twin psums
	int best = 0, as = 0, bs = 0;

	for(int i=0; i<n; ++i){
		as += a[i], bs += b[i];
		if(as == bs) best = i+1;
	}

	std::cout << best << '\n';
}
