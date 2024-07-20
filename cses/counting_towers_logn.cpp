// Counting Towers  -  https://cses.fi/problemset/task/2413/
//
// Normally done with constructive DP, resulting in complexity
// of O(n) per query. However, I show a matrix-based solution,
// which achieves O(log n) per query, and runs in <= 10ms on
// CSES.
//
// My original constructive DP solution is on this repo - read
// it first, as it'll explain `rel`

#include <iostream>

using LL = long long;

constexpr int M = 1e9 + 7;

// transformation matrix
LL rel[6][6]={
	{1,1,1,1,1,1},
	{1,1,1,1,0,0},
	{1,1,1,1,0,0},
	{1,1,1,1,0,0},
	{0,0,0,0,1,1},
	{1,1,1,1,1,1}
}, alt[6][6], rea[6][6], reb[6];

// multiply vector by matrix
void vmul(LL *v, LL (*m)[6]){
	for(int i=0; i<6; ++i) alt[0][i] = 0;
	for(int i=0; i<6; ++i)
		for(int j=0; j<6; ++j)
			alt[0][j] = (alt[0][j] + m[i][j]*v[i]) % M;
	for(int i=0; i<6; ++i) v[i] = alt[0][i];
}

// multiply matrix by itself
void mmul(LL (*m)[6]){
	for(int i=0; i<6; ++i)
		for(int j=0; j<6; ++j)
			alt[i][j] = 0;

	for(int i=0; i<6; ++i)
		for(int j=0; j<6; ++j)
			for(int a=0; a<6; ++a)
				alt[i][j] = (alt[i][j] + m[i][a]*m[a][j]) % M;

	for(int i=0; i<6; ++i)
		for(int j=0; j<6; ++j)
			m[i][j] = alt[i][j];
}

void test_case(){
	int n; std::cin >> n;

	for(int i=0; i<6; ++i){
		reb[i] = 1;
		for(int j=0; j<6; ++j)
			rea[i][j] = rel[i][j];
	}

	--n;

	// binary exponentiate *on the matrix and vector themselves*
	for(; n; n /= 2){
		if(n&1) vmul(reb, rea);
		mmul(rea);
	}

	std::cout << ((reb[0] + reb[5]) % M) << '\n';
}

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int t; std::cin >> t;
	while(t--) test_case();
}
