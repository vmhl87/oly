#include <iostream>
#include <array>
#include <set>

using ll = long long;
const int N = 5e5 + 2;

// "if i replace this with small to large treap merge then it works"
std::set<std::array<ll, 2>> b[N];
ll size[N], a[N][3];
bool ans[N];

int main(){
	int n; std::cin >> n;

	for(int i=0; i<n; ++i)
		for(int j=0; j<3; ++j)
			std::cin >> a[i+2][j];

	size[0] = 1, size[1] = 1;

	for(int i=2; i<n+2; ++i){
		size[i] = size[a[i][0]] + size[a[i][1]];
		if(size[i] > 2e18) size[i] = 2e18;
	}

	for(int i=n+1; i>1; --i){
		b[i].insert({a[i][2]-1, i-2});

		for(const auto &[v, x] : b[i]){
			if(v < size[a[i][0]]) b[a[i][0]].insert({v, x});
			else b[a[i][1]].insert({v-size[a[i][0]], x});
		}

		b[i].clear();
	}

	for(const auto &[v, x] : b[1]) ans[x] = 1;

	for(int i=0; i<n; ++i) std::cout << ans[i] << '\n';
}
