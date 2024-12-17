#include <algorithm>
#include <iostream>
#include <array>

using ll = long long;
const int N = 2e5;

std::array<ll, 3> a[N];
int b[N*3];

void test(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i)
		for(int j=0; j<2; ++j)
			std::cin >> a[i][j+1],
			a[i][0] += a[i][j+1];
	std::sort(a, a+n);

	for(int i=0; i<N*3; ++i) b[i] = 0;

	int res = 0;

	for(int i=0; i<n; ++i)
		for(int j=a[i][1]; j>=0; --j)
			b[j+a[i][2]] = std::max(b[j+a[i][2]], 1+b[j]),
				res = std::max(res, b[j+a[i][2]]);

	std::cout << res << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
