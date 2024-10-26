#include <algorithm>
#include <iostream>
#include <vector>
#include <array>

using ll = long long;

std::array<int, 2> a[200000];

bool downright(std::array<int, 2> x, std::array<int, 2> y){
	return x[0] >= y[0] && x[1] <= y[1];
}

int main(){
	int n, m; std::cin >> n >> m;
	for(int i=0; i<n; ++i)
		std::cin >> a[i][0] >> a[i][1];

	std::sort(a, a+n);

	int ld = 0;

	std::vector<std::array<int, 2>> hull;
	for(int i=0; i<n; ++i){
		if(a[i][0] > ld){
			while(hull.size() && downright(a[i], hull.back()))
				hull.pop_back();
			hull.push_back(a[i]);
			ld = a[i][0];
		}
	}

	ll res = 0;
	int height = m+1;

	for(int i=m; i; --i){
		if(hull.size() && hull.back()[0] == i){
			height = hull.back()[1];
			hull.pop_back();
		}
		res += height-i;
	}

	std::cout << res << '\n';
}
