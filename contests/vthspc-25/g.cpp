#include <iostream>

char a[100][100];

int main(){
	int n; std::cin >> n;

	for(int i=0; i<n; ++i){
		for(int j=0; j<n; ++j){
			std::cin >> a[i][j];
		}
	}

	for(int i=0; i<n; ++i)
		std::cout << char(a[i][i]^1);
	std::cout << '\n';
}
