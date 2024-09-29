#include "ricehub.h"

#include <algorithm>
#include <iostream>

using ll = long long;

int *a, n;
ll b;

int most(int i){
	int res = 1;
	ll rem = b;

	int l = i-1, r = i+1;
	ll ln = b+1, rn = b+1;

	if(l >= 0) ln = a[i] - a[l];
	if(r < n) rn = a[r] - a[i];

	while(ln <= rem || rn <= rem){
		if(ln < rn){
			++res, --l;
			rem -= ln;
			ln = b+1;
			if(l >= 0) ln = a[i] - a[l];
		}else{
			++res, ++r;
			rem -= rn;
			rn = b+1;
			if(r < n) rn = a[r] - a[i];
		}
	}

	return res;
}

int besthub(int N, int m, int A[], ll B){
	a = A, b = B, n = N;

	int res = most(0);
	for(int i=1; i<n; ++i) res = std::max(res, most(i));

	for(int i=0; i<n; ++i) std::cout << most(i) << " \n"[i==n-1];

	return res;
}
