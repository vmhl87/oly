#include "encoder.h"
#include "encoderlib.h"

#include <iostream>

void encode(int n, int m[]){
	if(n <= 32){
		for(int i=0; i<n; ++i){
			int hi = m[i] >> 6,
				mid = (m[i] >> 3) & 7,
				lo = m[i] & 7;

			for(int j=0; j<7; ++j){
				int block = i << 3;
				if(j < lo) block |= 1;
				if(j < mid) block |= 2;
				if(j < hi) block |= 4;
				send(block);
			}
		}
	}else{
		for(int i=0; i<n; ++i){
			int hi = m[i] >> 4,
				lo = m[i] & 15;

			for(int j=0; j<15; ++j){
				int block = i << 2;
				if(j < lo) block |= 1;
				if(j < hi) block |= 2;
				send(block);
			}
		}
	}
}

// SPLIT

#include "decoder.h"
#include "decoderlib.h"

#include <iostream>

void decode(int n, int l, int x[]){
	int out[64] = {};

	if(n <= 32){
		for(int i=0; i<l; ++i){
			int idx = x[i] >> 3;
			if(x[i] & 1) ++out[idx];
			if(x[i] & 2) out[idx] += 8;
			if(x[i] & 4) out[idx] += 64;
		}
	}else{
		for(int i=0; i<l; ++i){
			int idx = x[i] >> 2;
			if(x[i] & 1) ++out[idx];
			if(x[i] & 2) out[idx] += 16;
		}
	}

	for(int i=0; i<n; ++i) output(out[i]);
}
