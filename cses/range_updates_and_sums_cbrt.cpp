// ends up being slower than sqrt actually
//  + i havent gotten set query to work

#include <iostream>

using LL = long long;
const LL sz = 64, szz = 4096;

int n;
// raw, x2{sum, add query, set query}
LL a[300000], b[4000][3], c[64][3];

void push(int i){
	int l1 = i/sz, l2 = i/szz;

	if(c[l2][2]){
		for(int j=0; j<sz; ++j) b[j+l2*sz][2] = c[l2][2],
			b[j+l2*sz][1] = 0, b[j+l2*sz][0] = c[l2][2]*sz;
		c[l2][2] = 0;
	}
	if(c[l2][1]){
		for(int j=0; j<sz; ++j) b[j+l2*sz][1] += c[l2][1],
			b[j+l2*sz][0] += c[l2][2]*sz;
		c[l2][1] = 0;
	}

	if(b[l1][2]){
		for(int j=0; j<sz; ++j) a[j+l1*sz] = b[l1][2];
		b[l1][2] = 0;
	}
	if(b[l1][1]){
		for(int j=0; j<sz; ++j) a[j+l1*sz] += b[l1][1];
		b[l1][1] = 0;
	}
}

int main(){
	int q; std::cin >> n >> q;
	for(int i=0; i<n; ++i) std::cin >> a[i],
		b[i/sz][0] += a[i], c[i/szz][0] += a[i];

	while(q--){
		int t; std::cin >> t;

		if(t == 1){
			int l, r, x; std::cin >> l >> r >> x, --l, --r;

			push(l), push(r);

			if(l/szz == r/szz){
				if(l/sz == r/sz)
					for(int i=l; i<=r; ++i)
						a[i] += x, b[i/sz][0] += x, c[i/szz][0] += x;
				else{
					for(int i=1+l/sz; i<r/sz; ++i)
						b[i][0] += x*sz, b[i][1] += x, c[l/szz][0] += x;
					for(int i=l; i/sz==l/sz; ++i)
						a[i] += x, b[l/sz][0] += x, c[l/szz][0] += x;
					for(int i=sz*(r/sz); i<=r; ++i)
						a[i] += x, b[r/sz][0] += x, c[r/szz][0] += x;
				}
			}else{
				for(int i=1+l/szz; i<r/szz; ++i)
					c[i][0] += x*szz, c[i][1] += x;
				for(int i=1+l/sz; i<sz*(1+l/szz); ++i)
					b[i][0] += x*sz, b[i][1] += x, c[i/sz][0] += x;
				for(int i=sz*(r/szz); i<r/sz; ++i)
					b[i][0] += x*sz, b[i][1] += x, c[i/sz][0] += x;
				for(int i=l; i/sz==l/sz; ++i)
					a[i] += x, b[i/sz][0] += x, c[i/szz][0] += x;
				for(int i=sz*(r/sz); i<=r; ++i)
					a[i] += x, b[i/sz][0] += x, c[i/szz][0] += x;
			}

		}else if(t == 2){
			int l, r, x; std::cin >> l >> r >> x, --l, --r;

			push(l), push(r);

			if(l/szz == r/szz){
				if(l/sz == r/sz)
					for(int i=l; i<=r; ++i)
						b[i/sz][0] += x-a[i], c[i/szz][0] += x-a[i], a[i] = x;
				else{
					for(int i=1+l/sz; i<r/sz; ++i)
						b[i][2] = x, b[i][1] = 0, c[l/szz][0] += x*sz-b[i][0], b[i][0] = x*sz;
					for(int i=l; i/sz==l/sz; ++i)
						b[l/sz][0] += x-a[i], c[l/szz][0] += x-a[i], a[i] = x;
					for(int i=sz*(r/sz); i<=r; ++i)
						b[r/sz][0] += x-a[i], c[r/szz][0] += x-a[i], a[i] = x;
				}
			}else{
				for(int i=1+l/szz; i<r/szz; ++i)
					c[i][0] = x*szz, c[i][2] = x, c[i][1] = 0;
				for(int i=1+l/sz; i<sz*(1+l/szz); ++i)
					b[i][2] = x, b[i][1] = 0, c[i/sz][0] += x*sz-b[i][0], b[i][0] = x*sz;
				for(int i=sz*(r/szz); i<r/sz; ++i)
					b[i][2] = x, b[i][1] = 0, c[i/sz][0] += x*sz-b[i][0], b[i][0] = x*sz;
				for(int i=l; i/sz==l/sz; ++i)
					b[i/sz][0] += x-a[i], c[i/szz][0] += x-a[i], a[i] = x;
				for(int i=sz*(r/sz); i<=r; ++i)
					b[i/sz][0] += x-a[i], c[i/szz][0] += x-a[i], a[i] = x;
			}

		}else{
			int l, r; std::cin >> l >> r, --l, --r;

			LL sum = 0;

			push(l), push(r);

			if(l/szz == r/szz){
				if(l/sz == r/sz) for(int i=l; i<=r; ++i) sum += a[i];
				else{
					for(int i=1+l/sz; i<r/sz; ++i) sum += b[i][0];
					for(int i=l; i/sz==l/sz; ++i) sum += a[i];
					for(int i=sz*(r/sz); i<=r; ++i) sum += a[i];
				}
			}else{
				for(int i=1+l/szz; i<r/szz; ++i) sum += c[i][0];
				for(int i=1+l/sz; i<sz*(1+l/szz); ++i) sum += b[i][0];
				for(int i=sz*(r/szz); i<r/sz; ++i) sum += b[i][0];
				for(int i=l; i/sz==l/sz; ++i) sum += a[i];
				for(int i=sz*(r/sz); i<=r; ++i) sum += a[i];
			}

			std::cout << sum << '\n';
		}
	}
}
