#include <iostream>

using ll = long long;
const int N = 2e5;

ll a[N], b[N], t[N*2], n;

int main(){
	int q; std::cin >> n >> q;

	for(int i=0; i<n; ++i) std::cin >> a[i];
	for(int i=0; i<n; ++i) std::cin >> b[i];

	for(int i=0; i<n; ++i) t[i+n] = std::min(a[i], b[i]);
	for(int i=n-1; i; --i) t[i] = t[i*2] + t[i*2+1];

	while(q--){
		char c;
		int x, v;
		std::cin >> c >> x >> v, --x;

		if(c == 'A') a[x] = v;
		else b[x] = v;

		t[x+n] = std::min(a[x], b[x]);
		for(int i=(x+n)/2; i; i/=2)
			t[i] = t[i*2] + t[i*2+1];

		std::cout << t[1] << '\n';
	}
}
