// CCO '20 P2 Exercise Deadlines  -  https://dmoj.ca/problem/cco20p2

#include <algorithm>
#include <iostream>
#include <array>

using LL = long long;

std::array<int, 2> a[200000];

int main(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> a[i][0], a[i][1] = i;

	std::sort(a, a+n);

	LL swaps = 0;

	for(int i=0; i<n; ++i){
		swaps += std::abs(i - a[i][1]);

		if(a[i][0] <= i){
			std::cout << "-1\n";
			return 0;
		}
	}

	std::cout << swaps << '\n';
}
