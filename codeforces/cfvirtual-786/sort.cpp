#include <iostream>

void test_case(){
	int n; std::cin >> n;
	int a[n]; for(int i=0; i<n; ++i) std::cin >> a[i];

	for(int i=n-2; i>=0; i-=2) if(a[i] > a[i+1]){
		a[i] ^= a[i+1];
		a[i+1] ^= a[i];
		a[i] ^= a[i+1];
	}

	int v = 0;

	for(int x : a){
		if(x < v){
			std::cout << "NO\n";
			return;
		}
		v = x;
	}

	std::cout << "YES\n";
}

int main(){
	int t; std::cin >> t;

	while(t--) test_case();
}
