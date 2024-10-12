#include <iostream>

char b[4000][4000];
int n;

char rotate(int i, int j){
	int dist = 1+std::min(
			std::min(i, n-i-1),
			std::min(j, n-j-1)
		);
	dist %= 4;
	dist = 4-dist;
	int x = i, y = j;
	while(dist--){
		int ny = n-1-x;
		x = y, y = ny;
	}
	return b[x][y];
}

int main(){
	std::cin >> n;

	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j)
			std::cin >> b[i][j];

	for(int i=0; i<n; ++i){
		for(int j=0; j<n; ++j)
			std::cout << rotate(i, j);
		std::cout << '\n';
	}
}
