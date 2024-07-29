#include <algorithm>
#include <iostream>
#include <array>
#include <cmath>

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int n, m; std::cin >> n >> m;

	int a[n], b[n];
	for(int i=0; i<n; ++i) std::cin >> a[i];
	for(int i=0; i<n; ++i) std::cin >> b[i];

	std::array<int, 2> d[n];
	for(int i=0; i<n; ++i) d[i][0] = a[i] - b[i], d[i][1] = a[i];

	std::sort(d, d+n);

	int N = 1 << (1 + std::__lg(n - 1));

	std::array<int, 2> seg[N*2];

	for(int i=0; i<n; ++i) seg[i+N][0] = d[i][0], seg[i+N][1] = d[i][1];
	for(int i=n; i<N; ++i) seg[i+N][0] = 1e7, seg[i+N][1] = 1e7;

	for(int i=N-1; i; --i) seg[i][1] = std::min(seg[i<<1][1], seg[i<<1|1][1]);

	long long res = 0;

	for(int i=0; i<m; ++i){
		int c; std::cin >> c;

		while(1){
			// must find el in seg with [1] <= c
			// fail when global min req too big
			if(seg[1][1] > c) break;

			int p = 1;

			while(p < N){
				if(seg[p<<1][1] > c) p = p<<1|1;
				else p <<= 1;
			}

			// std::cout << "current: " << c << "\n  choice: " << seg[p][0] << ',' << seg[p][1] << '\n';

			int req = seg[p][1], am = seg[p][0];

			res += 1 + (c - req) / am;
			c -= (1 + (c - req) / am) * am;
		}
	}

	std::cout << res*2 << '\n';
}
