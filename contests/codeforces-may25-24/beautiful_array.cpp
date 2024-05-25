#include <algorithm>
#include <iostream>
#include <cmath>

void test_case(){
	int n; std::cin >> n;
	int a[n]; for(int i=0; i<n; ++i) std::cin >> a[i];
	std::sort(a, a+n);
	int p = n;
	for(int i=1; i<n; ++i){
		if(a[i] % a[0] == 0) a[i] = 0;
		else p = std::min(p, i);
	}
	for(int i=p+1; i<n; ++i) if(a[i] % a[p] != 0){
		std::cout << "No\n";
		return;
	}
	std::cout << "Yes\n";
}

int main(){
	int t; std::cin >> t;
	while(t--) test_case();
}
