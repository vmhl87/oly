#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>

char a[200000]; //, b[300000], c[300000];

int main(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> a[i], a[i] -= '0';

	// c = 0, b = 0
	boost::multiprecision::cpp_int c = 0, b = 0;

	for(int i=0; i<n; ++i){
		// c = c*10 + (i+1)*a[i]
		// b += c
		c = c*10 + (i+1)*a[i];
		b += c;
	}

	std::cout << b << '\n';
}
