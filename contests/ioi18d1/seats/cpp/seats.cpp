#include "seats.h"

const int bsz = 1024;
std::vector<int> up[1000], down[1000], loc;
int len, hcp;

void push(int i){
	up[i].clear(), down[i].clear();
	up[i].push_back(loc[i*bsz]);
	down[i].push_back(loc[i*bsz]);
	for(int j=1+i*bsz; j<i*bsz+bsz&&j<len; ++j){
		if(loc[j] > up[i].back()) up[i].push_back(loc[j]);
		if(loc[j] < down[i].back()) down[i].push_back(loc[j]);
	}
}

void give_initial_chart(int H, int W, std::vector<int> R, std::vector<int> C) {
	hcp = H;
	if(H == 1){
		loc.resize(C.size()), len = C.size();
		for(int i=0; i<len; ++i) loc[i] = C[i];
		for(int i=0; i*bsz<len; ++i) push(i);
	}
}

int swap_seats(int a, int b) {
	if(hcp != 1) return 0;
	// swap loc of a, b
	std::swap(loc[a], loc[b]);
	// then rebuild both of a, b
	push(a/bsz); if(a/bsz != b/bsz) push(b/bsz);

	int lo = down[0].back(), hi = up[0].back(),
		ans = down[0].size() + up[0].size() - 1;

	for(int i=1; i*bsz<len; ++i){
		// process lo
		// if definitely less add all
		if(down[i][0] < lo){
			lo = down[i].back();
			ans += down[i].size();

		// skip if too high
		}else if(down[i].back() < lo){
			// we want to find the first element
			// that is less than lo
			int l = 0, r = down[i].size() - 1;
			while(l < r){
				int m = (l+r)/2;
				if(down[i][m] > lo) l = m+1;
				else r = m;
			}
			lo = down[i][l];
			ans += down[i].size() - l;
		}

		// process hi
		// if definitely more add all
		if(up[i][0] > hi){
			hi = up[i].back();
			ans += up[i].size();

		// skip if too low
		}else if(up[i].back() > hi){
			// we want to find the first element
			// that is more than hi
			int l = 0, r = up[i].size() - 1;
			while(l < r){
				int m = (l+r)/2;
				if(up[i][m] < hi) l = m+1;
				else r = m;
			}
			hi = up[i][l];
			ans += up[i].size() - l;
		}
	}

	return ans;
}
