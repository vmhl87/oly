#include <algorithm>
#include <iostream>
#include <array>

using ll = long long;
const int N = 2e5;

std::array<int, 2> a[N];
std::array<int, 3> b[N];

int main(){
	int n, m; std::cin >> n >> m;

	for(int i=0; i<n; ++i){
		int l, r, p; std::cin >> l >> r >> p;
		--l, --r;
		a[i] = {l, p};
		b[i] = {r, l, p};
	}

	ll x = 0, d = 0;

	std::sort(a, a+n);
	std::sort(b, b+n);

	int p1 = 0, p2 = 0;

	for(int i=0; i<m; ++i){
		while(p1<n && a[p1][0] == i)
			d += a[p1++][1];
		x += d;
		std::cout << x << " \n"[i==m-1];
		while(p2<n && b[p2][0] == i){
			ll f = (ll)b[p2][2] * (b[p2][0]-b[p2][1]+1);
			d -= b[p2++][2], x -= f;
		}
	}
}
