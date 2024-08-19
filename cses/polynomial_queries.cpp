#include <iostream>

using ll = long long;

ll a[200000], b[800], u[800], x[800];

void push(int i){
	if(u[i]){
		for(int j=0; j<512; ++j) a[j+i*512] += u[i];
		u[i] = 0;
	}
	if(x[i]){
		for(int j=1; j<512; ++j) a[j+i*512] += j*x[i];
		x[i] = 0;
	}
}

int main(){
	std::cin.tie(0) -> sync_with_stdio();

	int n, m; std::cin >> n >> m;
	for(int i=0; i<n; ++i) std::cin >> a[i], b[i/512] += a[i];

	while(m--){
		ll t, l, r; std::cin >> t >> l >> r, --l, --r;

		if(t&1){
			if(l/512 == r/512){
				push(l/512);
				for(int i=l; i<=r; ++i) a[i] += (i-l+1);
				b[l/512] += ((r-l+1)*(r-l+2))/2;
			}else{
				push(l/512), push(r/512);
				for(int i=l; i/512==l/512; ++i)
					a[i] += (i-l+1), b[i/512] += (i-l+1);
				for(int i=1+l/512; i<r/512; ++i)
					b[i] += (i*512-l+1)*512 + 130816, u[i] += (i*512-l+1), ++x[i];
				for(int i=r; i/512==r/512; --i)
					a[i] += (i-l+1), b[i/512] += (i-l+1);
			}
		}else{
			ll res = 0;
			if(l/512 == r/512){
				push(l/512);
				for(int i=l; i<=r; ++i) res += a[i];
			}else{
				push(l/512), push(r/512);
				for(int i=l; i/512==l/512; ++i) res += a[i];
				for(int i=1+l/512; i<r/512; ++i) res += b[i];
				for(int i=r; i/512==r/512; --i) res += a[i];
			}
			std::cout << res << '\n';
		}
	}
}
