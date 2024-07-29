#include <algorithm>
#include <iostream>

int m[100];

int main(){
	int n; std::cin >> n;

	for(int i=0; i<n; ++i) std::cin >> m[i];

	std::sort(m, m+n);

	// low tide and high tide markers
	int l = (n-1)/2, r = l+1, par = 1;

	// push to extremes
	while(l+1 || r < n){
		if(par) std::cout << m[l--] << ' ';
		else std::cout << m[r++] << ' ';
		par ^= 1;
	}

	std::cout << '\n';
}
