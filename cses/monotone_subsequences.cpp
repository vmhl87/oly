#include <iostream>

int a[100], b[100], *p;

void test_case(){
	int n, k; std::cin >> n >> k;
	if(n > k*k) std::cout << "IMPOSSIBLE\n";
	else{
		p = a;

		int first = 0, diff = n - (n/k) * k;
		for(int i=0; i<k; ++i){
			for(int j=n/k + (i<diff); j; --j) std::cout << first + j << ' ',
				*(p++) = first + j;
			first += n/k + (i<diff);
		}

		std::cout << '\n';
	}
}

int main(){
	int t; std::cin >> t;
	while(t--) test_case();
}
