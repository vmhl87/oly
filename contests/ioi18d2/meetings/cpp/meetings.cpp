#include <algorithm>
#include <iostream>
#include <array>
#include "meetings.h"

// really simple divide and conquer, idk
long long best(std::vector<int> &h, long long l, long long r){
	if(l > r) return 0;
	long long max = h[l], maxi = l;
	for(int i=l+1; i<=r; ++i)
		if(h[i] > max) max = h[i], maxi = i;

	return std::min(
			(maxi-l+1)*max + best(h, maxi+1, r),
			(r-maxi+1)*max + best(h, l, maxi-1)
		);
}

std::vector<long long> minimum_costs(std::vector<int> H, std::vector<int> L,
                                     std::vector<int> R) {
  int Q = L.size(), n = H.size();
  std::vector<long long> C(Q);
  if(H.size() <= 5000 && Q <= 5000 && 0){
	  for (int j = 0; j < Q; ++j) {
		C[j] = best(H, L[j], R[j]);
	  }
  }else{
	  std::vector<std::array<int, 2>> ranges;
	  int current = 0, l = 0;
	  for(int i=0; i<n; ++i){
		  if(H[i] == 1) ++current;
		  else{
			  if(current != 0){
				  ranges.push_back({l, i-1});
			  }
			  current = 0;
			  l = i+1;
		  }
	  }
	  if(current != 0) ranges.push_back({l, n-1});
	  int sz = 1 << (1 + std::__lg(ranges.size()));
	  std::vector<std::array<int, 2>> tree(sz*2);
	  for(int i=0; i<(int)ranges.size(); ++i)
		  tree[i+sz] = ranges[i];
	  for(int i=(int)ranges.size(); i<sz; ++i)
		  tree[i+sz] = {n, n};
	  for(int i=sz-1; i; --i){
		  if(tree[i<<1][1]-tree[i<<1][0] > tree[i<<1|1][1]-tree[i<<1|1][0])
			  tree[i] = tree[i<<1];
		  else tree[i] = tree[i<<1|1];
	  }
	  for(int i=0; i<Q; ++i){
		  std::array<int, 2> lr = {L[i], -1}, rl = {R[i], -1};
		  int l = std::upper_bound(ranges.begin(), ranges.end(), lr) - ranges.begin();
		  int r = std::upper_bound(ranges.begin(), ranges.end(), rl) - ranges.begin();
		  //std::cout << l << ',' << r << '\n';
		  if(r < (int)ranges.size() && ranges[r][1] <= R[i]) ++r;
		  //std::cout << l << ',' << r << '\n';
		  int best = 0;
		  if(l && ranges[l-1][1] >= L[i])
			  best = std::max(best, ranges[l-1][1]-L[i]+1);
		  if(r < (int)ranges.size() && ranges[r][0] <= R[i])
			  best = std::max(best, R[i]-ranges[r][0]+1);
		  //std::cout << best << '\n';
		  for(l += sz, r += sz; l < r; l >>= 1, r >>= 1){
			  if(l&1) best = std::max(best, tree[l][1]-tree[l++][0]+1);
			  if(r&1) best = std::max(best, tree[--r][1]-tree[r][0]+1);
		  }
		  //std::cout << best << '\n';
		  C[i] = 2LL * (long long)(R[i]-L[i]+1) - (long long)best;
	  }
  }
  return C;
}
