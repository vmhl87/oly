#include "seats.h"

std::vector<int> c, tree;
int len;

void add(int l, int r, int v){
	for(l += len, r += len; l < r; l >>= 1, r >>= 1){
		if(l&1) tree[l++] += v;
		if(r&1) tree[--r] += v;
	}
}

void proc(int i, int v){
	int a = c[i], b = c[i+1];
	if(a > b) std::swap(a, b);
	add(a, b, v);
}

void give_initial_chart(int H, int W, std::vector<int> R, std::vector<int> C) {
	len = C.size();
	c.resize(len+2);
	c[0] = len;
	for(int i=0; i<len; ++i) c[i+1] = C[i];
	c[len] = len;
	len += 2;
	tree.resize(len*2);
	for(int i=1; i<len; ++i) proc(i-1, 1);
}

int swap_seats(int a, int b) {
	++a, ++b;
	if(std::abs(a-b) == 1){
		proc(std::min(a, b), -1);
		proc(std::min(a, b)-1, -1);
		proc(std::max(a, b), -1);
		std::swap(c[a], c[b]);
		proc(std::min(a, b), 1);
		proc(std::min(a, b)-1, 1);
		proc(std::max(a, b), 1);
	}else{
		proc(a-1, -1);
		proc(a, -1);
		proc(b-1, -1);
		proc(b, -1);
		std::swap(c[a], c[b]);
		proc(a-1, 1);
		proc(a, 1);
		proc(b-1, 1);
		proc(b, 1);
	}
}
