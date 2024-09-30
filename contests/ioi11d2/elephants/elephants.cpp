#include "elephants.h"

#include <iostream>

// r: idx -> pos, rr: pos -> idx
int n, l, *x, r[50000], rr[50000];

void init(int N, int L, int X[]){
	n = N, l = L, x = X;
	for(int i=0; i<n; ++i) r[i] = i, rr[i] = i;
}

int update(int i, int y){
	x[i] = y;

	int p = r[i];

	while(p > 0 && y < x[rr[p-1]]){
		int b = p-1, c = rr[b];

		int t = rr[p];
		rr[p] = rr[b];
		rr[b] = t;

		--r[i], --p;
		++r[c];
	}

	while(p < n-1 && y > x[rr[p+1]]){
		int b = p+1, c = rr[b];

		int t = rr[p];
		rr[p] = rr[b];
		rr[b] = t;

		++r[i], ++p;
		--r[c];
	}

	int res = 0, lpos = -2e9;
	for(int i=0; i<n; ++i) if(x[rr[i]] > lpos + l) ++res, lpos = x[rr[i]];

	return res;
}
