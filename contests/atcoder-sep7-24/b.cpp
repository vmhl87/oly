#include <iostream>

int to[101][101];

int main(){
	int n; std::cin >> n;

	for(int i=1; i<=n; ++i){
		for(int j=1; j<=i; ++j)
			std::cin >> to[i][j];
	}

	int a = 1;

	for(int i=1; i<=n; ++i){
		if(a<i) a = to[i][a];
		else a = to[a][i];
	}

	std::cout << a << '\n';
}
