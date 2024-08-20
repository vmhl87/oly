#include <iostream>

void test_case(){
	int n; std::cin >> n;
	if(n&1){
		for(int i=0; i<n/2; ++i){
			std::cout << n-i << ' ';
		}
		for(int i=1; i<=1+n/2; ++i){
			std::cout << i << ' ';
		}
		std::cout << '\n';
	}else std::cout << "-1\n";
}

int main(){
	int t; std::cin >> t;
	while(t--) test_case();
}
