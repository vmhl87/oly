#include <iostream>
#include <vector>
#include <stack>

void test_case(){
	int n, m; std::cin >> n >> m;

	std::vector<int> adj[n];

	for(int i=0; i<m; ++i){
		int a, b; std::cin >> a >> b, --a, --b;

		adj[a].push_back(b), adj[b].push_back(a);
	}

	int depth[n] = {1}, parent[n] = {-1}, at[n] = {}, delta[n] = {}, now = 0;

	int size[n];
	long long best = ((long long)n * (long long)(n-1)) / 2;
	for(int i=0; i<n; ++i) size[i] = 1;

	std::stack<int> dfs; dfs.push(0);

	while(dfs.size()){
		int top = dfs.top();

		if(at[top] == adj[top].size()){
			dfs.pop();

			now += delta[top];

			if(dfs.size()){
				if(now == 0){
					long long cur = (long long)size[top] * (long long)(size[top]-1);
					cur += (long long)(n-size[top]) * (long long)(n-size[top]-1);

					cur /= 2;

					if(best == 0 || cur < best) best = cur;
				}

				delta[dfs.top()] += now, now = 0;

				size[dfs.top()] += size[top];
			}
		}else{
			int next = adj[top][at[top]];

			if(!depth[next])
				dfs.push(next), depth[next] = depth[top] + 1, parent[next] = top;
			else if(depth[next] < depth[top] && next != parent[top]){
				++delta[top], --delta[next];
			}

			++at[top];
		}
	}

	std::cout << best << '\n';
}

int main(){
	int n; std::cin >> n;

	while(n--) test_case();
}
