// Key observation here is that an arrangement of
// data is only valid if it is sorted in order both
// left -> right and top -> bottom, so we can just
// check the four corners

#include <iostream>

int data[100][100], next[100][100], n;

bool check(){
	return data[0][0] < data[0][n-1] && data[0][0] < data[n-1][0] &&
		data[0][n-1] < data[n-1][n-1] && data[n-1][0] < data[n-1][n-1];
}

void rotate(){
	for(int i=0; i<n; ++i) for(int j=0; j<n; ++j)
		next[j][n-1-i] = data[i][j];
	for(int i=0; i<n; ++i) for(int j=0; j<n; ++j)
		data[i][j] = next[i][j];
}

int main(){
	std::cin >> n;
	for(int i=0; i<n; ++i) for(int j=0; j<n; ++j) std::cin >> data[i][j];

	for(int i=0; i<4; ++i){
		if(check()){
			// silly io (im lazy)
			for(int i=0; i<n; ++i) for(int j=0; j<n; ++j)
				std::cout << data[i][j] << " \n"[j==n-1];
			break;
		}
		rotate();
	}
}
