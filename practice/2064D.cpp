// URL: https://codeforces.com/problemset/problem/2064/D

#include <iostream>

const int N = 2e5;

int a[N], P[N+1], n, c[30][N+1];

int f(int l, int r, int b){
	return c[b][r] - c[b][l];
}

int g(int l, int r){
	return P[r] ^ P[l];
}

void test(){
	int q; std::cin >> n >> q;

	for(int i=n-1; i>=0; --i) std::cin >> a[i];

	for(int i=0; i<n; ++i) P[i+1] = P[i] ^ a[i];

	for(int j=0; j<30; ++j) for(int i=0; i<n; ++i)
		c[j][i+1] = c[j][i] + (a[i] >= (1<<j));

	while(q--){
		int x, p=0; std::cin >> x;

		for(int i=29; i>=0 && p<n; --i){
			if(x < a[p]) break;

			if(x & (1<<i)){
				int I = p;

				for(int s=1<<18; s; s/=2)
					if(f(p, std::min(I+s, n), i) == 0)
						I = std::min(I+s, n);

				x ^= g(p, I);
				p = I;

				if(I < n){
					if(x < a[I]) break;
					x ^= a[I], ++p;
				}
			}
		}

		std::cout << p << ' ';
	}

	std::cout << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
