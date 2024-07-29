#include <iostream>

void test_case(){
	int n; std::cin >> n;
	int a[n]; for(int i=0; i<n; ++i) std::cin >> a[i];
	int count(0);
	for(int i=1; i<n; ++i) if(a[i-1] > a[i]) ++count;
	if(n > 1 && a[n-1] > a[0]) ++count;
	if(count > 1) std::cout << "No";
	else std::cout << "Yes";
	std::cout << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test_case();
}
