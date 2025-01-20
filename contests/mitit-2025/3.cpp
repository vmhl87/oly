#include <algorithm>
#include <iostream>

using ll = long long;
const int N = 2e5;

ll a[N];

void test(){
	int t; std::cin >> t;

	for(int i=0; i<t; ++i){
		ll j; std::cin >> j >> a[i];
		a[i] += j;
	}

	std::sort(a, a+t);

	std::cout << (a[t-1] - a[0])*2 << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
