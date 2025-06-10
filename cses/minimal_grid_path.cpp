#include <algorithm>
#include <iostream>
#include <vector>
#include <array>

char a[3000][3000];

std::vector<std::array<int, 3>> b[2];
int r = 1, o = 0;

int main(){
	int n; std::cin >> n;

	for(int i=0; i<n; ++i)
		for(int j=0; j<n; ++j)
			std::cin >> a[i][j];

	b[0].push_back({a[0][0], 0, 0});

	std::cout << a[0][0];

	for(int i=0; i<n+n-2; ++i){
		for(const auto &[x, y, z] : b[o]){
			if(y+1 < n) b[r].push_back({a[y+1][z], y+1, z});
			if(z+1 < n) b[r].push_back({a[y][z+1], y, z+1});
		}

		std::sort(b[r].begin(), b[r].end());
		b[r].erase(std::unique(b[r].begin(), b[r].end()), b[r].end());
		auto it = std::lower_bound(b[r].begin(), b[r].end(), (std::array<int, 3>){b[r][0][0], n, n});
		b[r].erase(it, b[r].end());

		std::cout << (char)b[r][0][0];

		b[o].clear();

		r ^= 1, o ^= 1;
	}

	std::cout << '\n';
}
