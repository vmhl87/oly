#include <iostream>

bool a[1000][1000];
int b[1000][1000];

int main(){
	int n, m; std::cin >> n >> m;

	for(int i=0; i<n; ++i)
		for(int j=0; j<m; ++j){
			char c; std::cin >> c;
			a[i][j] = c == '*';
		}

	int best = 0;

	for(int i=0; i<n; ++i){
		for(int l=0; l<m; ++l){
			bool w = 1;
			for(int r=l; r<m; ++r){
				if(a[i][r]) w = 0;
				if(w){
					best = std::max(best,
							(r-l+1) * (i+1-b[l][r]));
				}else{
					b[l][r] = i+1;
				}
			}
		}
	}

	std::cout << best << '\n';
}
