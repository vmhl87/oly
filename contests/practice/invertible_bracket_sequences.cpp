#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <map>

void test_case(){
	std::string s; std::cin >> s;

	int n = s.length()+1;

	int heights[n]; heights[0] = 0;

	std::map<int, std::vector<int>> loc;

	for(int i=0; i<n-1; ++i){
		loc[heights[i]].push_back(i);

		if(s[i] == '(') heights[i+1] = heights[i] + 1;
		else heights[i+1] = heights[i] - 1;
	}

	int tree[n<<1];
	for(int i=0; i<n; ++i) tree[i+n] = heights[i];
	for(int i=n-1; i; --i) tree[i] = std::max(tree[i<<1], tree[i<<1|1]);

	long long res = 0;

	std::map<int, int> pos;

	for(int i=0; i<n; ++i){
		// allowed max height = h*2
		int max = heights[i] << 1;

		int ol = pos[heights[i]]++, r = loc[heights[i]].size()-1;
		int l = ol;

		while(l < r){
			int mid = (l + r + 1) >> 1;

			// check if mid works
			// segtree query from [i, loc[height[i]][mid]]
			int d = i, u = loc[heights[i]][mid]+1, ret = 0;

			for(d += n, u += n; d < u; d >>= 1, u >>= 1){
				if(d & 1) ret = std::max(ret, tree[d++]);
				if(u & 1) ret = std::max(ret, tree[--u]);
			}

			if(ret > max) r = mid-1;
			else l = mid;
		}

		// ol -> l total elem
		// literally just diff i think
		res += (long long)l - (long long)ol;
	}

	std::cout << res << '\n';
}

int main(){
	int t; std::cin >> t;

	while(t--) test_case();
}
