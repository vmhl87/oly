#include <iostream>

const int N = 1e4;

int b[N][N], a[N];

int main(){
	int n, q; std::cin >> n >> q;
	for(int i=0; i<n; ++i) std::cin >> a[i], --a[i];

	for(int i=0; i<n; ++i){
		++b[i][0];
		int lp = i-1, rp = i+1;

		for(int j=1; j<n; ++j){
			if(lp < 0){
				++b[rp][j];
				++rp;
			}else if(rp >= n){
				++b[lp][j];
				--lp;
			}else{
				if(a[lp] < a[rp]){
					++b[lp][j];
					--lp;
				}else{
					++b[rp][j];
					++rp;
				}
			}
		}
	}

	for(int i=0; i<q; ++i){
		int x, y; std::cin >> x >> y;
		std::cout << b[--x][--y] << '\n';
	}
}
