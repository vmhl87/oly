#include <iostream>

const int sz = 256;
int a[200000], b[800];

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int n, m; std::cin >> n >> m;
	for(int i=0; i<n; ++i) std::cin >> a[i],
		b[i/sz] = std::max(b[i/sz], a[i]);
	b[1+(n-1)/sz] = 1<<30;

	for(int x=0; x<m; ++x){
		int r; std::cin >> r;

		int j=0; while(b[j] < r) ++j;
		j *= sz; if(j >= n){std::cout << 0 << " \n"[x==m-1]; continue;}
		while(a[j] < r) ++j;

		std::cout << j+1 << " \n"[x==m-1], a[j] -= r, j /= sz, b[j] = 0;
		for(int i=0; i<sz; ++i) b[j] = std::max(b[j], a[i+j*sz]);
	}
}
