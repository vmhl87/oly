#include <iostream>

using ll = long long;
const int N = 3e5;

ll d[N], e[N];

int main(){
	int n, l; std::cin >> n >> l;
	for(int i=1; i<n; ++i) std::cin >> d[i], d[i] += d[i-1];

	if(l%3){
		std::cout << 0 << '\n';
		return 0;
	}

	for(int i=0; i<n; ++i) ++e[d[i]%l];

	ll c = 0;

	for(int i=0; i<l; ++i) c += e[i] * e[(i+l/3)%l] * e[(i+2*l/3)%l];

	std::cout << c/3 << '\n';
}
