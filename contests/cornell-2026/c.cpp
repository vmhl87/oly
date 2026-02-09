#include <algorithm>
#include <iostream>
#include <array>

const int N = 2e5;

int root[N];

int find(int i){
	if(root[i] < 0) return i;
	else return root[i] = find(root[i]);
}

int merge(int i, int j){
	i = find(i), j = find(j);

	if(i == j) return 1;

	if(i<j) root[i] += root[j], root[j] = i;
	else root[j] += root[i], root[i] = j;

	return 0;
}

std::array<int, 3> a[N];

int main(){
	int n, m; std::cin >> n >> m;

	for(int i=0; i<n; ++i) root[i] = -1;

	for(int i=0; i<m; ++i){
		std::cin >> a[i][0] >> a[i][1] >> a[i][2], --a[i][0], --a[i][1];
	}

	std::sort(a, a+m, [] (std::array<int, 3> x, std::array<int, 3> y){
		return x[2] < y[2];
	});

	int res = 0;

	for(int i=0; i<m; ++i) res += merge(a[i][0], a[i][1]);

	std::cout << res << '\n';
}
