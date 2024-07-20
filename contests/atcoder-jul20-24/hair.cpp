#include <algorithm>
#include <iostream>

int l[100];

int main(){
	int n, t, p; std::cin >> n >> t >> p;
	
	for(int i=0; i<n; ++i) std::cin >> l[i];

	std::sort(l, l+n);

	std::cout << std::max(0, t - *(l+n-p)) << '\n';
}
