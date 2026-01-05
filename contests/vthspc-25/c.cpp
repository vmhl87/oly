#include <iostream>

int a[100][100];

int main(){
	int n, m; std::cin >> n >> m;
	int s; std::cin >> s;

	for(int i=0; i<n; ++i){
		for(int j=0; j<m; ++j){
			std::cin >> a[i][j];
		}
	}

	int res = 0;

	for(int i=1; i<n-1; ++i){
		for(int j=1; j<m-1; ++j){
			if(a[i][j] == s){
				if((a[i-1][j-1]+a[i-1][j+1]+a[i+1][j-1]+a[i+1][j+1])%s == 0){
					++res;
				}
			}
		}
	}

	std::cout << res << '\n';
}
