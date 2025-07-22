#include <iostream>
#include <vector>
#include <queue>
#include <array>

using ll = long long;
const int N = 2e5;

std::vector<int> b[N];
int a[N], d[N][2];
bool v[N][2];

void test(){
	int n, q, l; std::cin >> n >> q >> l;
	for(int i=0; i<l; ++i) std::cin >> a[i];

	for(int i=0; i<n; ++i) b[i].clear();

	for(int i=0; i<q; ++i){
		int x, y; std::cin >> x >> y, --x, --y;
		b[x].push_back(y), b[y].push_back(x);
	}

	std::queue<std::array<int, 2>> f;

	for(int i=0; i<n; ++i) v[i][0] = 0, v[i][1] = 0;
	for(int i=0; i<n; ++i) d[i][0] = 1e18, d[i][1] = 1e18;

	f.push({0, 0}), v[0][0] = 1;

	while(f.size()){
		auto [i, j] = f.front(); f.pop();

		d[i][j&1] = j, ++j;

		for(int x : b[i]) if(!v[x][j&1]){
			v[x][j&1] = 1;
			f.push({x, j});
		}
	}

	// for(int i=0; i<n; ++i) std::cout << d[i][0] << " \n"[i==n-1];
	// for(int i=0; i<n; ++i) std::cout << d[i][1] << " \n"[i==n-1];
	// std::cout << '\n';

	ll m[2] = {-1, -1}, M = 0, mm = 1e18;

	for(int i=0; i<l; ++i){
		if((a[i]&1) && a[i] < mm) mm = a[i];
		M += a[i];
	}

	m[M&1] = M;
	if(mm&1) M -= mm;
	m[M&1] = M;

	for(int i=0; i<n; ++i) std::cout << (d[i][0] <= m[0] || d[i][1] <= m[1]);
	std::cout << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
