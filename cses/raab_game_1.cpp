#include <iostream>

void test(){
	int n, a, b; std::cin >> n >> a >> b;

	if(a+b > n || ((a == 0 || b == 0) && a+b != 0)){
		std::cout << "NO\n";
		return;
	}

	std::cout << "YES\n";

	for(int i=0; i<n; ++i) std::cout << i+1 << " \n"[i==n-1];
	for(int i=0, j=a+b; i<n; ++i) std::cout << (i<j ? (i+a)%j+1 : i+1) << " \n"[i==n-1];
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
