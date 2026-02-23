#include <algorithm>
#include <iostream>
#include <array>

const int N = 2e5;

std::array<int, 2> a[N];

int sz[N];
std::array<std::array<int, 2>, 2> b[N];

int l[N], r[N], ct;

bool Z(std::array<int, 2> a, std::array<int, 2> b){
	return a[1] < b[1];
}

int dfs(int lb, int rb, int s){
	if(lb+1 == rb){
		int i = ct++;

		sz[i] = 1;

		b[i] = (std::array<std::array<int, 2>, 2>){
			(std::array<int, 2>){a[lb][0], a[lb][0]},
			(std::array<int, 2>){a[lb][1], a[lb][1]}
		};

		return i;
	}

	if(s) std::sort(a+lb, a+rb);
	else std::sort(a+lb, a+rb, Z);

	int m = (lb+rb)/2;

	int i = ct++;

	l[i] = dfs(lb, m, !s);
	r[i] = dfs(m, rb, !s);

	sz[i] = sz[l[i]] + sz[r[i]];

	b[i] = {
		(std::array<int, 2>){
			std::min(b[l[i]][0][0], b[r[i]][0][0]),
			std::max(b[l[i]][0][1], b[r[i]][0][1]),
		},
		(std::array<int, 2>){
			std::min(b[l[i]][1][0], b[r[i]][1][0]),
			std::max(b[l[i]][1][1], b[r[i]][1][1]),
		},
	};

	return i;
}

bool in(std::array<std::array<int, 2>, 2> a, std::array<std::array<int, 2>, 2> b){
	return b[0][0] >= a[0][0] && b[0][1] <= a[0][1] && b[1][0] >= a[1][0] && b[1][1] <= a[1][1];
}

bool on(std::array<std::array<int, 2>, 2> a, std::array<std::array<int, 2>, 2> b){
	return b[0][1] >= a[0][0] && b[0][0] <= a[0][1] && b[1][1] >= a[1][0] && b[1][0] <= a[1][1];
}

int count(std::array<std::array<int, 2>, 2> q, int i){
	if(!on(q, b[i])) return 0;
	if(in(q, b[i])) return sz[i];

	return count(q, l[i]) + count(q, r[i]);
}

int main(){
	int n, q; std::cin >> n >> q;
	for(int i=0; i<n; ++i) std::cin >> a[i][1], a[i][0] = i;

	dfs(0, n, 0);

	while(q--){
		int w, x, y, z; std::cin >> w >> x >> y >> z;
		std::cout << count({std::array<int, 2>{w, x}, std::array<int, 2>{y, z}}, 0) << '\n';
	}
}
