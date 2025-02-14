#include <algorithm>
#include <iostream>
#include <cassert>
#include <array>

#include "seats.h"

const int MAXN = 1000000;
int dt[MAXN*4], mn[MAXN*4], ct[MAXN*4], R[MAXN], C[MAXN];
std::vector<std::vector<int>> c, stat;
int len;

void add(int l, int r, int i, int lb, int rb, int v){
	if(l>r) return;
	if(l==lb&&r==rb) dt[i] += v, mn[i] += v;
	else{
		int m = (lb+rb)/2;
		add(l, std::min(m, r),   i*2,   lb, m,   v);
		add(std::max(m+1, l), r, i*2+1, m+1, rb, v);
		
		if(mn[i*2] == mn[i*2+1])
			mn[i] = dt[i]+mn[i*2], ct[i] = ct[i*2] + ct[i*2+1];
		else if(mn[i*2] > mn[i*2+1])
			mn[i] = dt[i]+mn[i*2+1], ct[i] = ct[i*2+1];
		else
			mn[i] = dt[i]+mn[i*2], ct[i] = ct[i*2];
	}
}

void proc(int i, int j, int v){
	stat[i][j] += v;
	int s[4] = {c[i][j], c[i+1][j], c[i][j+1], c[i+1][j+1]};
	std::sort(s, s+4);
	add(s[0], s[1]-1, 1, 0, len-1, v);
	add(s[2], s[3]-1, 1, 0, len-1, v);
}

int build(int i, int l, int r){
	if(l==r) return ct[i] = 1;
	else return ct[i] = build(i*2, l, (l+r)/2) + build(i*2+1, 1+(l+r)/2, r);
}

void give_initial_chart(int H, int W, std::vector<int> rr, std::vector<int> cc) {
	len = rr.size();
	c.resize(H+2, std::vector<int>(W+2, len));
	stat.resize(H+1, std::vector<int>(W+1));
	for(int i=0; i<len; ++i) c[rr[i]+1][cc[i]+1] = i, R[i] = rr[i], C[i] = cc[i];
	build(1, 0, len-1);
	for(int i=0; i<=H; ++i) for(int j=0; j<=W; ++j) proc(i, j, 1);
}

int swap_seats(int a, int b) {
	if(stat[R[a]]   [C[a]]  ) proc(R[a],   C[a],   -1);
	if(stat[R[a]+1] [C[a]]  ) proc(R[a]+1, C[a],   -1);
	if(stat[R[a]]   [C[a]+1]) proc(R[a],   C[a]+1, -1);
	if(stat[R[a]+1] [C[a]+1]) proc(R[a]+1, C[a]+1, -1);

	if(stat[R[b]]   [C[b]]  ) proc(R[b],   C[b],   -1);
	if(stat[R[b]+1] [C[b]]  ) proc(R[b]+1, C[b],   -1);
	if(stat[R[b]]   [C[b]+1]) proc(R[b],   C[b]+1, -1);
	if(stat[R[b]+1] [C[b]+1]) proc(R[b]+1, C[b]+1, -1);

	std::swap(c[R[a]+1][C[a]+1], c[R[b]+1][C[b]+1]);

	std::swap(R[a], R[b]);
	std::swap(C[a], C[b]);

	if(!stat[R[a]]   [C[a]]  ) proc(R[a],   C[a],   1);
	if(!stat[R[a]+1] [C[a]]  ) proc(R[a]+1, C[a],   1);
	if(!stat[R[a]]   [C[a]+1]) proc(R[a],   C[a]+1, 1);
	if(!stat[R[a]+1] [C[a]+1]) proc(R[a]+1, C[a]+1, 1);

	if(!stat[R[b]]   [C[b]]  ) proc(R[b],   C[b],   1);
	if(!stat[R[b]+1] [C[b]]  ) proc(R[b]+1, C[b],   1);
	if(!stat[R[b]]   [C[b]+1]) proc(R[b],   C[b]+1, 1);
	if(!stat[R[b]+1] [C[b]+1]) proc(R[b]+1, C[b]+1, 1);

	return ct[1];
}
