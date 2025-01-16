#include <iostream>

const int N = 2e4;

int a[N];

int main(){
	int n, k; std::cin >> n >> k;

	for(int i=0; i<n; ++i)
		for(int j=0; j<k; ++j){
			char x; std::cin >> x;
			a[i] = a[i]*2 + x-'0';
		}

	int res = k;

	for(int i=0; i<n; ++i)
		for(int j=i+1; j<n; ++j)
			res = std::min(res, __builtin_popcount(a[i]^a[j]));

	std::cout << res << '\n';
}
