#include <algorithm>
#include <iostream>
#include "doll.h"

int flip(int i, int p){
	int res = 0;
	for(int j=0; j<p; ++j) if(i&(1<<j))
		res |= 1<<(p-j-1);
	return res;
}

int build(int root, int pow, int offset, std::vector<int> &to,
		std::vector<int> &x, std::vector<int> &y, int l, int r){
	if(pow == 1){
		if(l-offset >= 0) x.push_back(to[l-offset]);
		else x.push_back(root);
		y.push_back(to[r-offset]);
		/*
		x.push_back(to[l]);
		if(r < (int)to.size()) y.push_back(to[r]);
		else y.push_back(root);
		*/
		return -(int)x.size();
	}else{
		x.push_back(0);
		y.push_back(0);
		int cur = (int)x.size() - 1;
		if((l+r)/2 >= offset){
			int left = build(root, pow-1, offset, to, x, y, l, (l+r)/2);
			x[cur] = left;
		}else x[cur] = root;
		int right = build(root, pow-1, offset, to, x, y, 1+(l+r)/2, r);
		y[cur] = right;
		/*
		int left = build(root, pow-1, offset, to, x, y, l, (l+r)/2);
		x[cur] = left;
		if((l+r)/2 < (int)to.size()){
			int right = build(root, pow-1, offset, to, x, y, 1+(l+r)/2, r);
			y[cur] = right;
		}else y[cur] = root;
		*/
		return -1-cur;
	}
}

void create_circuit(int m, std::vector<int> a){
	int n = a.size();
	std::vector<int> c(m+1), x, y;

	std::vector<int> to[m+1];
	to[0].push_back(a[0]);

	for(int i=0; i<n-1; ++i)
		to[a[i]].push_back(a[i+1]);

	to[a.back()].push_back(0);

	for(int i=0; i<=m; ++i){
		if(to[i].size() == 1) c[i] = to[i][0];
		else if(to[i].size() == 2){
			x.push_back(to[i][0]);
			y.push_back(to[i][1]);
			c[i] = -(int)x.size();
		}else if(to[i].size() > 2){
			int sz = to[i].size();
			int pow = 1 + std::__lg(sz - 1);
			sz = 1 << pow;
			int offset = sz - to[i].size();

			std::vector<int> order(to[i].size());
			std::vector<std::pair<int, int>> conv(to[i].size());
			for(int j=0; j<(int)to[i].size(); ++j)
				conv[j].first = flip(j+offset, pow), conv[j].second = j;
			std::sort(conv.begin(), conv.end());
			
			for(int j=0; j<(int)to[i].size(); ++j)
				order[conv[j].second] = to[i][j];

			c[i] = -1-(int)x.size();
			build(c[i], pow, offset, order, x, y, 0, sz-1);
			
			/*
			int root = -1-(int)x.size();
			for(int j=1; j<sz; ++j){
				if(j*2 < sz){
					x.push_back(root+1 - j*2);
					y.push_back(root - j*2);
				}else{
					int xid = j*2-sz;
					int yid = xid+1;

					// convolute by flipping
					xid = flip(xid, pow);
					yid = flip(yid, pow);

					xid -= offset, yid -= offset;

					if(xid >= 0)
						x.push_back(to[i][xid]);
					else x.push_back(root);

					if(yid >= 0)
						y.push_back(to[i][yid]);
					else y.push_back(root);
				}
			}

			c[i] = root;
			*/

			/*
			int end = switchid--;
			x.push_back(to[i][0]), y.push_back(to[i][1]);

			for(int j=2; j<to[i].size(); ++j){
				x.push_back(end), y.push_back(to[i][j]);
				--end, --switchid;
			}

			c[i] = end;
			*/
		}
	}

	answer(c, x, y);
}
