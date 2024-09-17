#include "rail.h"

#include <iostream>
#include <cassert>
#include <set>

int alldist[5001][5001];
std::set<int> seen;
int n;

// nlogn
int next(int i){
	int best = 1<<29, res = -1;

	for(int j=0; j<n; ++j) if(!seen.count(j) && i!=j)
		if(alldist[i][j] < best) best = alldist[i][j], res = j;

	assert(res != -1);

	return res;
}

int cls(int i){
	int best = 1<<29;

	for(int j=0; j<n; ++j) if(j!=i)
		if(alldist[i][j] < best) best = alldist[i][j];

	return best;
}

// n^2 logn
void findLocation(int N, int first, int location[], int stype[]){
	n = N;

	int calls = 0;

	for(int i=0; i<n; ++i)
		for(int j=i+1; j<n; ++j)
			alldist[i][j] = getDistance(i, j),
				alldist[j][i] = alldist[i][j],
				++calls;
	
	assert(calls == (n * (n-1))/2);

	location[0] = first, stype[0] = 1;
	seen.insert(0);

	int ldx = 0, rdx = next(0);
	location[rdx] = first + alldist[0][rdx];
	stype[rdx] = 2;
	seen.insert(rdx);

	for(int x=2; x<n; ++x){
//std::cout << "ldx, rdx: " << ldx << ' ' << rdx << '\n';

		int i = next(ldx),
			d1 = alldist[ldx][i], d2 = alldist[rdx][i];

//std::cout << "found " << i << " (" << d1 << ' ' << d2 << ")\n";

		// left of ldx
		if(d1 - 2*cls(ldx) == d2 - (location[rdx]-location[ldx])){
			stype[i] = 1;
			location[i] = location[rdx] - d2;
			ldx = i;
		// right of rdx
		}else if(d2 - 2*cls(rdx) == d1 - (location[rdx]-location[ldx])){
			stype[i] = 2;
			location[i] = location[ldx] + d1;
			rdx = i;
		// middle D
		}else if(d2 - d1 == location[rdx]-location[ldx]){
			stype[i] = 2;
			location[i] = location[ldx] + d1;
		// middle C
		}else{
			stype[i] = 1;
			location[i] = location[rdx] - d2;
		}

//std::cout << "@ " << location[i] << '\n';

		seen.insert(i);
	}

//for(int i=0; i<n; ++i) std::cout << stype[i] << ' ' << location[i] << '\n';
}
