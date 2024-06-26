#include <iostream>
#include <cmath>

void test_case(){
	int n, m; std::cin >> n >> m;

	int mat[n][m];

	for(int i=0; i<n; ++i)
		for(int j=0; j<m; ++j)
			std::cin >> mat[i][j];

	for(int i=0; i<n; ++i){
		for(int j=0; j<m; ++j){
			if(j) std::cout << ' ';

			int next = 0, works = 1;

			if(i){
				if(mat[i][j] > mat[i-1][j]) next = std::max(next, mat[i-1][j]);
				else works = 0;
			}
			if(j){
				if(mat[i][j] > mat[i][j-1]) next = std::max(next, mat[i][j-1]);
				else works = 0;
			}
			if(i < n-1){
				if(mat[i][j] > mat[i+1][j]) next = std::max(next, mat[i+1][j]);
				else works = 0;
			}
			if(j < m-1){
				if(mat[i][j] > mat[i][j+1]) next = std::max(next, mat[i][j+1]);
				else works = 0;
			}

			if(works) mat[i][j] = next;
			
			std::cout << mat[i][j];
		}

		std::cout << '\n';
	}
}

int main(){
	int t; std::cin >> t;

	while(t--) test_case();
}
