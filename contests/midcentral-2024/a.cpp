#include <iostream>

int a[50];

int main(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> a[i];

	int l = a[0], r = a[0];

	for(int i=1; i<n; ++i)
		l = std::min(l, a[i]),
		  r = std::max(r, a[i]);

	std::cout << l - std::min(l, r/2) << '\n';
}
