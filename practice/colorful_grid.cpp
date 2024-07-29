// https://codeforces.com/contest/1898/problem/C
//
// "cheesable" by noticing that you can just create
// a 1x1 square cycle in the starting corner and two
// possible paths that come off of it and it will 
// always work given that K is of proper parity

#include <iostream>

void test_case(){
	int n, m, k; std::cin >> n >> m >> k;

	if((n+m+k)&1 || k < (n+m-2)) std::cout << "NO\n";
	else{
		std::cout << "YES\n";

		char rows[n][m-1], cols[m][n-1];

		for(int i=0; i<n; ++i)
			for(int j=0; j<m-1; ++j)
				rows[i][j] = 'R';

		for(int i=0; i<m; ++i)
			for(int j=0; j<n-1; ++j)
				cols[i][j] = 'R';

		cols[1][0] = 'B';
		cols[0][0] = 'B';

		for(int i=2; i<m-1; i+=2)
			rows[1][i] = 'B';

		for(int i=1; i<n-1; i+=2)
			cols[0][i] = 'B';

		for(int i=n&1; i<m-1; i+=2)
			rows[n-1][i] = 'B';

		for(int i=2-(m&1); i<n-1; i+=2)
			cols[m-1][i] = 'B';

		for(int i=0; i<n; ++i)
			for(int j=0; j<m-1; ++j)
				std::cout << rows[i][j] << " \n"[j==m-2];

		for(int i=0; i<n-1; ++i)
			for(int j=0; j<m; ++j)
				std::cout << cols[j][i] << " \n"[j==m-1];
	}
}

int main(){
	int t; std::cin >> t;

	while(t--) test_case();
}
