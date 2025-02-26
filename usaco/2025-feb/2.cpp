#include <iostream>

using ll = long long;
const int N = 2e5, M = 1e9+7;

bool a[N], b[N+1];
int d[N+1];
ll c[N+1];

const int Q = 1e5;
ll lo[Q+1], hi[Q+1];

ll p(int i){
	return lo[i%Q]*hi[i/Q] % M;
}

int count_ones(int l, int r){
	return d[r]-d[l];
}

ll slice(int l, int r){
	ll res = c[r] - c[l]*p(r-l)%M;
	if(res < 0) res += M;
	return res;
}

int main(){
	int n, m, q; std::cin >> n >> m >> q;

	lo[0] = 1;
	for(int i=0; i<1e5; ++i) lo[i+1] = lo[i]*2 % M;
	hi[0] = 1;
	for(int i=0; i<1e5; ++i) hi[i+1] = hi[i]*lo[Q] % M;

	for(int i=0; i<m; ++i){
		int l, r; std::cin >> l >> r;
		b[l-1] ^= 1, b[r] ^= 1;
	}

	bool x = 0;
	
	for(int i=0; i<n; ++i){
		x ^= b[i];
		a[i] = x;
		c[i+1] = (c[i]*2+x) % M;
		d[i+1] = d[i]+x;
	}

	while(q--){
		int l, r, k; std::cin >> l >> r >> k, --l;

		if(count_ones(l, r) >= k){
			std::cout << (p(k)+M-1)%M << '\n';

		}else{
			int x = k-count_ones(l, r), l2 = l;

			for(int i=1<<18; i; i/=2)
				if(l2+i <= r && (r-l2-i)-count_ones(l2+i, r) >= x)
					l2 += i;

			ll res = p(k-(r-l2))-1;
			if(res < 0) res += M;
			res = (slice(l2, r) + res*p(r-l2)) % M;

			std::cout << res << '\n';
		}
	}
}
