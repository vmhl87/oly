
#include "decoder.h"
#include "decoderlib.h"

#include <algorithm>
#include <iostream>
#include <array>

std::array<int, 2> a[64];

void decode(int n, int l, int x[]){
	for(int i=0; i<l; ++i){
		a[i][0] = x[i] >> 2;
		a[i][1] = x[i] & 3;
	}

	std::sort(a, a+l);

	for(int i=0; i<n; ++i){
		int t = 0;
		for(int j=0; j<4; ++j){
			t += a[i*4+j][1] << (j*2);
		}
		output(t);
	}
}
