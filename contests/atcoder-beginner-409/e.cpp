#include <iostream>
#include <vector>
#include <array>

using ll = long long;
const int N = 1e5;

std::vector<std::array<int, 2>> v[N];

ll x[N], w[N], res;

void dfs(int i, int p){
	w[i] = x[i];

	for(const auto &[j, W] : v[i]) if(j != p)
		dfs(j, i), w[i] += w[j], res += std::abs(w[j]) * W;
}

int main(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> x[i];
	for(int i=1; i<n; ++i){
		int a, b, c; std::cin >> a >> b >> c;
		--a, --b;
		v[a].push_back({b, c});
		v[b].push_back({a, c});
	}

	dfs(0, 0);

	std::cout << res << '\n';
}
