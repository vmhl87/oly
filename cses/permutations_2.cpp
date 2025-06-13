#include <iostream>

using ll = long long;
const int m = 1e9 + 7;

ll a[1001], b[1001];

int main(){
	int n; std::cin >> n;

	a[1] = 1, b[1] = 1;

	for(int i=2; i<=n; ++i){
		b[i] = a[i-1] * i % m;
		a[i] = b[i-1] * (i-2) % m;
	}

	std::cout << a[n] << '\n';
}
