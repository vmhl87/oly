#include "encoder.h"
#include "encoderlib.h"

#include <iostream>

void encode(int n, int m[]){
	for(int i=0; i<n; ++i){
		for(int j=0; j<4; ++j){
			int t = (i*4+j) << 2;
			t |= ((m[i] >> (j*2)) & 3);
			send(t);
		}
	}
}

// SPLIT
