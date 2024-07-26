#include <iostream>

const int sz = 256;
int a[200000], b[800];

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int n; std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> a[i], ++b[i/sz];

	for(int i=0; i<n; ++i){
		int p, j=0; std::cin >> p;

		while(p > b[j]) p -= b[j], ++j;
		j *= sz; while(p) p -= (a[j]>0), ++j;

		std::cout << a[--j] << " \n"[i==n-1];
		a[j] = 0, --b[j/sz];
	}
}
