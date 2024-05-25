#include <algorithm>
#include <iostream>
#include <array>
#include <set>

void test_case(){
	int n; std::cin >> n;
	std::array<int, 2> a[n];
	for(int i=0; i<n; ++i) std::cin >> a[i][0], a[i][1] = i;
	std::sort(a, a+n);
	std::set<int> s;
	for(int i=n-1; i>=0; --i){
		int v = a[i][1];
		s.insert(v);
// for(int x : s) std::cout << x << ' '; std::cout << '\n';
		auto l = s.find(v), r = l;
		if(l != s.begin()){
			if(v - *(--l) < 3){
				std::cout << a[i][0] << '\n';
				return;
			}
		}
		++r;
		if(r != s.end() && *r - v < 3){
			std::cout << a[i][0] << '\n';
			return;
		}
	}
}

int main(){
	int t; std::cin >> t;
	while(t--) test_case();
}
