// Fill in the Matrix  -  https://codeforces.com/contest/1869/problem/C
//
// So we can notice a pattern that generates us optimal
// configuration for a matrix with 1 more column than row:
//
//   r = 3, c = 4
//
//   0 1 2 3
//   1 2 3 0
//   2 3 0 1
//
//   3 0 1 2 -> 4
//
// We can extend this: for any matrix with rows >= columns-1,
// just repeat this structure. Otherwise, take off rows from
// the bottom side, and it will decrease MEX:
//
//   r = 3, c = 5
//
//   0 1 2 3 4
//   1 2 3 4 0
//   2 3 4 0 1
//
//   3 0 0 1 2 -> 4
//
// Then some edge case handling for cols = 0, and we are done

#include <iostream>

void test_case(){
	int n, m; std::cin >> n >> m;

	if(m == 1) std::cout << 0;
	else if(n >= m-1) std::cout << m;
	else std::cout << n+1;
	std::cout << '\n';

	for(int i=0; i<n; ++i){
		int shift = m == 1 ? 0 : i % (m-1);

		for(int j=0; j<m; ++j)
			std::cout << ((j+shift)%m) << " \n"[j==m-1];
	}
}

int main(){
	int t; std::cin >> t;
	while(t--) test_case();
}
