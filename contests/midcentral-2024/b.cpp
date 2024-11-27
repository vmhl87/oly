#include <algorithm>
#include <iostream>
#include <array>
#include <queue>
#include <set>

using ll = long long;

int a[42];

int main(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> a[i];

	std::sort(a, a+n);

	std::priority_queue<std::array<ll, 2>> q;

	q.push({0, (1ll<<42)-1});
	ll last = 1;

	std::set<ll> vis;

	while(q.size()){
		ll sum = q.top()[0], m = q.top()[1];
		q.pop();

		if(vis.count(m)) continue;
		vis.insert(m);

		if(sum == last) std::cout << -sum << '\n', exit(0);
		last = sum;

		for(int i=0; i<n; ++i) if(m&(1ll<<i))
			q.push({sum - a[i], m ^ (1ll<<i)});
	}
}
