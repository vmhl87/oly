#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <set>

int n, m;
int a[1001][1001];

std::map<int, std::vector<std::array<int, 2>>> of;
std::set<int> vis;

void dfs(int x){
	if(vis.count(x)) return;
	vis.insert(x);

	if(of.count(x))
		for(const auto &[i, j] : of[x])
			dfs(a[i][j]);
}

int main(){
	std::cin >> n >> m;

	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			std::cin >> a[i][j],
			of[i*j].push_back({i, j});

	dfs(1);

	std::cout << (vis.count(n*m) ? "yes" : "no") << '\n';
}
