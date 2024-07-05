#include <iostream>
#include <stack>
#include <map>

typedef long long LL;

void test_case(){
	int n; std::cin >> n;
	LL a[n]; for(int i=0; i<n; ++i) std::cin >> a[i];
	std::stack<int> adj[n];

	for(int i=1; i<n; ++i){
		int b; std::cin >> b;
		adj[b-1].push(i);
	}

	std::stack<int> dfs;
	int shortest[n] = {};
	LL res = 0, sum[n] = {};
	bool leaf[n] = {};
	for(int i=0; i<n; ++i) if(!adj[i].size()) leaf[i] = 1;
	std::map<int, LL> free[n];

	dfs.push(0);

	while(dfs.size()){
		int t = dfs.top();

		if(adj[t].size()) dfs.push(adj[t].top()), adj[t].pop();
		else{
			if(!leaf[t]){
				if(a[t] < sum[t]){
					free[t][0] = sum[t] - a[t];
				}else if(a[t] > sum[t]){
					LL diff = a[t] - sum[t];

					while(free[t].size()){
						auto x = free[t].begin();

						if(x->first > shortest[t]) break;

						if(diff > x->second){
							diff -= x->second;
							res += (LL)x->first * x->second;
							free[t].erase(x->first);
						}else{
							free[t][x->first] -= diff;
							res += diff * x->first;
							diff = 0;
							break;
						}
					}

					if(diff) res += diff * shortest[t];
				}
			}
			dfs.pop();
			if(dfs.size()){
				int x = dfs.top();
				if(!shortest[x] || shortest[t]+1 < shortest[x])
					shortest[x] = shortest[t]+1;
				sum[x] += a[t];
				for(const auto &[k, v] : free[t]){
					if(k+1 >= shortest[x]) break;
					free[x][k+1] += v;
				}
				free[t].clear();
			}
		}
	}

	std::cout << res << '\n';
}

int main(){
	int t; std::cin >> t;

	while(t--) test_case();
}
