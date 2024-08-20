#include <algorithm>
#include "doll.h"

int flip(int i, int p){
	int res = 0;
	for(int j=0; j<p; ++j) if(i&(1<<j))
		res |= 1<<(p-j-1);
	return res;
}

int build(int pow, int offset, std::vector<int> &a,
		std::vector<int> &x, std::vector<int> &y, int l, int r){
	if(pow == 1){
		if(l-offset >= 0) x.push_back(a[l-offset]);
		else x.push_back(-1);
		y.push_back(a[r-offset]);
		return -(int)x.size();
	}else{
		x.push_back(0);
		y.push_back(0);
		int cur = (int)x.size() - 1;
		if((l+r)/2 >= offset){
			int left = build(pow-1, offset, a, x, y, l, (l+r)/2);
			x[cur] = left;
		}else x[cur] = -1;
		int right = build(pow-1, offset, a, x, y, 1+(l+r)/2, r);
		y[cur] = right;
		return -1-cur;
	}
}

void create_circuit(int m, std::vector<int> a){
	std::vector<int> c(m+1, -1), x, y;
	a.push_back(0);

	int sz = a.size();
	int pow = 1 + std::__lg(sz - 1);
	sz = 1 << pow;

	int offset = sz - a.size();

	std::vector<int> order(a.size());
	std::vector<std::pair<int, int>> conv(a.size());
	for(int j=0; j<(int)a.size(); ++j)
		conv[j].first = flip(j+offset, pow), conv[j].second = j;
	std::sort(conv.begin(), conv.end());
	
	for(int j=0; j<(int)a.size(); ++j)
		order[conv[j].second] = a[j];

	build(pow, offset, order, x, y, 0, sz-1);

	answer(c, x, y);
}
