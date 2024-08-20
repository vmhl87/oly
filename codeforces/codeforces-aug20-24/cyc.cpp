#include <iostream>
#include <map>

void test_case(){
	int n; std::cin >> n;
	std::map<int, int> v;
	for(int i=0; i<n; ++i){
		int a; std::cin >> a;
		++v[a];
	}
	int max = 0;
	for(const auto &[a, count] : v)
		max = std::max(count, max);
	std::cout << n - max << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test_case();
}
