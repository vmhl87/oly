#include"holiday.h"

#include <iostream>

using ll = long long;

ll findMaxAttraction(int n, int start, int d, int attr[]) {
	ll best = 0;

	for(int i=0; i<1<<n; ++i){
		ll cons = 0;
		int l = start, r = start, count = 0;
		for(int j=0; j<n; ++j) if(i & (1<<j)){
			++count, l = std::min(l, j), r = std::max(r, j);
			cons += attr[j];
		}
		
		l = start-l, r = r-start;

		if(std::max(l, r) + 2*std::min(l, r) + count <= d)
			best = std::max(best, cons);
	}

	return best;
}
