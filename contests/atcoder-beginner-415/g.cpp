#include <iostream>

using ll = long long;
const int M = 2e5;

int a[M], b[M], c[900];

int main(){
	ll n; int m; std::cin >> n >> m;

	for(int i=0; i<m; ++i) std::cin >> a[i] >> b[i];

	int A = a[0], B = a[0]-b[0];

	for(int i=1; i<m; ++i)
		if(B*a[i] > A*(a[i]-b[i]))
			A = a[i], B = a[i]-b[i];

	ll rem = 1 + (n-600) / (ll) B, ct = 0;

	if(rem > 0)
		ct = rem * A, n -= (ll) B * rem;

	for(int i=1; i<900; ++i) c[i] = i;

	for(int i=1; i<900; ++i)
		for(int j=0; j<m; ++j) if(i >= a[j]){
			int d = c[i-a[j]+b[j]] + a[j];
			if(d > c[i]) c[i] = d;
		}

	std::cout << ct + c[n] << '\n';
}
