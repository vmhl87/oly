#include <algorithm>
#include <iostream>
#include <array>

const int N = 2e5;

std::array<int, 3> a[N*2];
int p[18][N+1], n;

std::array<int, 3> best(std::array<int, 3> a, std::array<int, 3> b){
	return a[1] < b[1] ? a : b;
}

int range(int r){
	int i = -1;
	for(int s=1<<18; s; s/=2)
		if(i+s < n && a[i+s+n][0] >= r) i += s;
	++i;
	std::array<int, 3> res = {0, (int)1e9, N};
	int j = n;
	for(i+=n; i>j; i/=2, j/=2){
		if(i&1) res = best(res, a[--i]);
		if(j&1) res = best(res, a[j++]);
	}
	return res[2];
}

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int q; std::cin >> n >> q;
	for(int i=0; i<n; ++i) std::cin >> a[i+n][0] >> a[i+n][1];
	std::sort(a+n, a+n+n);
	for(int i=0; i<n-i-1; ++i) std::swap(a[i+n], a[n+n-i-1]);
	for(int i=0; i<n; ++i) a[i+n][2] = i;

	for(int i=n-1; i; --i) a[i] = best(a[i*2], a[i*2+1]);
	for(int i=1; i<n; ++i) p[0][i] = range(a[i+n][1]);
	p[0][0] = p[0][N] = N;

	for(int i=1; i<18; ++i) for(int j=0; j<=N; ++j)
		p[i][j] = p[i-1][p[i-1][j]];

	while(q--){
		int l, r; std::cin >> l >> r;
		int d = range(l), res = 0;
		if(d < N && a[d+n][1] <= r) ++res;
		for(int i=17; i>=0; --i)
			if(p[i][d] < N && a[p[i][d]+n][1] <= r)
				d = p[i][d], res += 1<<i;
		std::cout << res << '\n';
	}
}
