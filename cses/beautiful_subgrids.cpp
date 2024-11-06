#include <iostream>

using ll = long long;

bool grid[3000][3000];

int main(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j){
			char c; std::cin >> c;
			grid[i][j] = c == '1';
		}

	ll res = 0;

	for(int i=0; i<n; ++i)
		for(int j=i+1; j<n; ++j){
			int part = 0;
			for(int k=0; k<n; ++k)
				if(grid[i][k] && grid[j][k])
					res += part, ++part;
		}

	std::cout << res << '\n';
}
