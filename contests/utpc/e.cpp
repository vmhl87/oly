#include <algorithm>
#include <iostream>
#include <array>
#include <queue>

using ll = long long;

std::array<int, 2> k[200000];

int main(){
	int n, d, x; std::cin >> n >> d >> x;

	for(int i=0; i<n; ++i) std::cin >> k[i][1];
	for(int i=0; i<n; ++i) std::cin >> k[i][0];

	std::sort(k, k+n);

	std::priority_queue<int> starts;

	while(x--) starts.push(0);

	ll res = 0;

	for(int i=n-1; i>=0; --i){
		int day = -starts.top(); starts.pop();
		if(day >= d) break;

		ll time = k[i][1];
		if(time > d-day) time = d-day;

		res += k[i][0] * time;
		starts.push(-day - time);
	}

	std::cout << res << '\n';
}
