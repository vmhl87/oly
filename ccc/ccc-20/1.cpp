#include <algorithm>
#include <iostream>
#include <array>

std::array<double, 2> a[100000];

int main(){
	int n; std::cin >> n;

	for(int i=0; i<n; ++i)
		std::cin >> a[i][0] >> a[i][1];

	std::sort(a, a+n);

	double max = 0;

	for(int i=1; i<n; ++i)
		max = std::max(max, std::abs(a[i][1] - a[i-1][1]) / (a[i][0] - a[i-1][0]));

	std::cout << max << '\n';
}
