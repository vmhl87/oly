#include <algorithm>
#include <iostream>
#include <array>
#include <queue>
#include <set>

std::array<int, 2> a[1000000];

int main(){
	int n, x; std::cin >> n >> x;
	for(int i=0; i<n; ++i)
		std::cin >> a[i][0], a[i][1] = i;
	std::sort(a, a+n);

	std::priority_queue<std::array<int, 3>> q;
	q.push({-a[0][0]-a[1][0], 0, 1});

	std::set<std::array<int, 2>> seen;

	while(q.size()){
		int sum = q.top()[0],
			i = q.top()[1],
			j = q.top()[2];
		q.pop();

		if(-sum > x) break;

		if(seen.count({i, j})) continue;
		seen.insert({i, j});

		int target = x + sum;
		std::array<int, 2> see = {target, -1};
		auto iter = std::lower_bound(a, a+n, see);
		if(iter != a+n && (*iter)[0] == target &&
				(*iter)[1] != a[i][1] && (*iter)[1] != a[j][1]){
			int ans[3] = {(*iter)[1], a[i][1], a[j][1]};
			std::sort(ans, ans+3);
			for(int i=0; i<3; ++i)
				std::cout << ans[i]+1 << " \n"[i==2];
			exit(0);
		}

		if(!seen.count({i, j+1}) && j+1 < n)
			q.push({-a[i][0]-a[j+1][0], i, j+1});

		if(!seen.count({i+1, j}) && i < j)
			q.push({-a[i+1][0]-a[j][0], i+1, j});
	}

	std::cout << -1 << '\n';
}
