// an attempt at using a state accumulation sort of thing
// it doesn't properly deal with cycles unfortunately

#include <iostream>
#include <vector>
#include <array>

using ll = long long;

const ll INF = 1LL << 60;
std::vector<std::array<int, 2>> adj[100000];
ll ans[100000][2];
bool in[100000];

ll best(int i, int use){
	if(i == 0) return 0;
	if(ans[i][use]) return ans[i][use];
	if(in[i]) return INF;
	in[i] = 1;
	ll res = INF;
	for(const auto &[x, cost] : adj[i]){
		if(use){
			res = std::min(res, std::min(
					cost + best(x, 1),
					cost/2 + best(x, 0)
				));
		}else res = std::min(res, cost + best(x, 0));
	}
	ans[i][use] = res;
	in[i] = 0;
	return res;
}

int main(){
	int n, m; std::cin >> n >> m;
	while(m--){
		int a, b, c; std::cin >> a >> b >> c;
		adj[b-1].push_back({a-1, c});
	}
	std::cout << best(n-1, 1) << '\n';
}
