#include <algorithm>
#include <iostream>
#include <array>
#include <queue>

using LL = long long;

std::array<int, 2> patch[200000];
int en[200000];
LL choice[200001][2];

LL bestrange(int l, int r, int el, int er){
	LL best = 0;
	for(int i=l; i<r; ++i){
		LL current = 0;
		for(int j=l; j<r; ++j)
			if(std::abs(patch[j][0] - patch[i][0]) < std::min(
						patch[j][0] - el, er - patch[j][0]))
				current += patch[j][1];
		if(current > best) best = current;
	}
	return best;
}

int main(){
	int n, m, k; std::cin >> k >> m >> n;

	for(int i=0; i<k; ++i) std::cin >> patch[i][0] >> patch[i][1];
	std::sort(patch, patch+k);

	en[0] = -2e9, en[m+1] = 2e9;
	for(int i=0; i<m; ++i) std::cin >> en[i+1];
	std::sort(en+1, en+m+1);

	// now do "two pointer" and go over all segments bounded by nhoj
	
	for(int i=1, p=0; i<=m+1; ++i){
		int l = p;
		while(patch[p][0] < en[i]) choice[i][1] += patch[p++][1];
		// do something with [l, p), en[i-1], en[i]
		choice[i][0] = bestrange(l, p, en[i-1], en[i]);
		if(patch[p][0] == en[i]) ++p;
	}

	std::priority_queue<std::array<int, 2>> q;
}
