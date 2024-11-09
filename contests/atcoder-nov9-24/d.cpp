#include <iostream>
#include <queue>

using ll = long long;

int main(){
	int q; std::cin >> q;

	std::queue<ll> p;
	ll now = 0;

	while(q--){
		int t; std::cin >> t;

		if(t==1) p.push(now);

		else{
			ll h; std::cin >> h;

			if(t&1){
				int res = 0;
				while(p.size() && p.front() <= now-h)
					++res, p.pop();
				std::cout << res << '\n';
			}else now += h;
		}
	}
}
