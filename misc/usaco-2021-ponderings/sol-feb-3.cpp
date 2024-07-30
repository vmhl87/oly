// Sweep line from top row to bottom row. Keep track of min across all ranges
// in each row, and accumulate. Overall not that complicated.

#include <iostream>

using LL = long long;

int board[500][500], range[500][500], gap[500][500];

int main(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i) for(int j=0; j<n; ++j) std::cin >> board[i][j];

	LL ans = 0;

	for(int i=0; i<n; ++i)
		for(int l=0; l<n; ++l){
			int min = board[i][l];
			for(int r=l; r<n; ++r){
				min = std::min(min, board[i][r]);
				if(min < 100){
					range[l][r] = 0;
					gap[l][r] = 0;
				}else{
					++gap[l][r];
					if(min == 100) range[l][r] += gap[l][r], gap[l][r] = 0;
					ans += range[l][r];
				}
			}
		}

	std::cout << ans << '\n';
}
