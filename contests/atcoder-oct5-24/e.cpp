#include <iostream>

using ll = long long;

int m[100][4];

ll at(int i, ll x, ll need){
	if(x < 0) return 1ll << 60;
	ll part = 1+(need-1-x*m[i][0])/m[i][2];
	if(x*m[i][0] >= need) part = 0;
	return part*m[i][3] + x*m[i][1];
}

ll good(int i, int x, int need){
	return at(i, x, need) < at(i, x-1, need);
}

int main(){
	int n, x; std::cin >> n >> x;
	for(int i=0; i<n; ++i){
		for(int j=0; j<4; ++j) std::cin >> m[i][j];
		if(m[i][1]*m[i][2] < m[i][0]*m[i][3])
			std::swap(m[i][0], m[i][2]), std::swap(m[i][1], m[i][3]);
	}

	int res = 0;

	for(int j=30; j>=0; --j){
		int cons = 1<<j | res;
		ll use = 0;

		for(int i=0; i<n; ++i){
			ll best = at(i, 0, cons);
			for(int x=1; x<110; ++x)
				best = std::min(best, at(i, x, cons));
			use += best;
			//int x = 0;
			//for(int k=25; k>=0; --k)
			//	if(good(i, 1<<k|x, cons)) x |= 1<<k;
			//use += at(i, x, cons);
		}

		//std::cout << "makes " << cons << " in " << use << '\n';

		if(use <= x) res = cons;
	}

	std::cout << res << '\n';
}
