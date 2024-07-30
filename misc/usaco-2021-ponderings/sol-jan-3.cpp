#include <iostream>

int board[1000][1000];

int main(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i) for(int j=0; j<n; ++j) std::cin >> board[i][j];

	int opt = 0;
	for(int i=0; i<n; ++i){
		int row[2] = {0, 0};
		for(int j=0; j<n; ++j)
			row[j&1] += board[i][j];
		opt += std::max(row[0], row[1]);
	}

	int prop = 0;
	for(int i=0; i<n; ++i){
		int row[2] = {0, 0};
		for(int j=0; j<n; ++j)
			row[j&1] += board[j][i];
		prop += std::max(row[0], row[1]);
	}

	std::cout << std::max(opt, prop) << '\n';
}
