#include "ricehub.h"

#include <algorithm>
#include <iostream>

using ll = long long;

int *a, n;
ll b;

ll lp[100001], rp[100001];

ll lsec(int l, int r){
	if(l>n-1) return b+1;
	if(r>n-1) return b+1;
	ll res = lp[r+1] - lp[l+1];
	res -= (ll)a[l] * (ll)(r-l);
	return res;
}

ll rsec(int l, int r){
	if(r<0) return b+1;
	if(l<0) return b+1;
	ll res = rp[l] - rp[r];
	res -= (ll)a[r] * (ll)(r-l);
	return -res;
}

ll cost(int i, int cover){
	if(cover&1){
		return rsec(i-cover/2, i) + lsec(i, i+cover/2);
	}else{
		int d = (cover-1)/2;
		return std::min(
				rsec(i-d, i) + lsec(i, i+d+1),
				rsec(i-d-1, i) + lsec(i, i+d)
			);
	}
}

int most(int i){
	int res = 1;

	for(int j=1<<20; j; j/=2)
		if(cost(i, res+j) <= b)
			res += j;

	return res;
}

int besthub(int N, int m, int A[], ll B){
	a = A, b = B, n = N;

	for(int i=0; i<n; ++i) lp[i+1] = lp[i] + a[i];
	for(int i=n; i; --i) rp[i-1] = rp[i] + a[i-1];

	int res = most(0);
	for(int i=1; i<n; ++i) res = std::max(res, most(i));

//	for(int i=0; i<n; ++i) std::cout << most(i) << " \n"[i==n-1];

	return res;
}
