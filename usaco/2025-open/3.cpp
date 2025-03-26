#include <algorithm>
#include <iostream>
#include <queue>
#include <array>

using ll = long long;
const int N = 1e5, M = 1e9+7;

ll m[N], mm[N];
ll n, d;

ll slice(ll v){
	ll res = 0;
	for(int i=0; i<n; ++i){
		if(m[i] <= v) break;
		res += std::min(d, m[i]-v);
	}
	return res;
}

int main(){
	std::cin >> n >> d;
	int a, b; std::cin >> a >> b;
	for(int i=0; i<n; ++i) std::cin >> m[i];

	std::sort(m, m+n, std::greater<ll>());

	for(int i=0; i<a; ++i) m[i] += d;

	ll x = m[0], mx = (ll)b * d;

	for(ll s=1ll<<34; s; s/=2)
		if(s<=x && slice(x-s) <= mx)
			x -= s;

	mx -= slice(x);
	for(int i=0; i<n; ++i){
		if(m[i] <= x) mm[i] = m[i];
		else mm[i] = std::max(m[i]-d, x);
	}

	ll res = 0;

	for(int i=0; i<n; ++i){
		ll z = mm[i]%M;
		res += z*z % M;
	}

	std::priority_queue<std::array<ll, 2>> q;
	
	for(int i=0; i<n; ++i) if(m[i]-mm[i] < d)
		q.push({mm[i], m[i]-mm[i]});

	while(mx--){
		std::array<ll, 2> x = q.top();
		q.pop();

		res = (res-((x[0]+x[0]-1)%M)+M)%M;

		if(x[1] < d) q.push(x);
	}

	std::cout << res%M << '\n';
}
