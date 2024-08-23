#include <iostream>
#include <cmath>

#include "seats.h"

std::vector<int> c, dt, mn, ct;
int len;

void prop(int i){
	if(i >= len) mn[i] = dt[i], ct[i] = 1;
	else{
		mn[i] = dt[i];
		if(mn[i<<1] == mn[i<<1|1])
			mn[i] += mn[i<<1], ct[i] = ct[i<<1] + ct[i<<1|1];
		else if(mn[i<<1] < mn[i<<1|1])
			mn[i] += mn[i<<1], ct[i] = ct[i<<1];
		else mn[i] += mn[i<<1|1], ct[i] = ct[i<<1|1];
	}
}

void grow(int i){
	for(; i; i >>= 1) prop(i);
}

void add(int l, int r, int v){
	for(l += len, r += len; l < r; l >>= 1, r >>= 1){
		if(l&1) dt[l] += v, grow(l++);
		if(r&1) dt[--r] += v, grow(r);
	}
}

void proc(int i, int v){
	//std::cout << "proc " << i << '.' << v << ':' << c[i] << ',' << c[i+1] << '\n';
	int a = c[i], b = c[i+1];
	if(a > b) std::swap(a, b);
	add(a, b, v);
}

void give_initial_chart(int H, int W, std::vector<int> R, std::vector<int> C) {
	len = C.size();
	c.resize(len+2);
	c[0] = len;
	for(int i=0; i<len; ++i) c[i+1] = C[i];
	c[len+1] = len;
	//len += 2;
	dt.resize(len*2), mn.resize(len*2), ct.resize(len*2);
	for(int i=0; i<len; ++i) ct[len+i] = 1;
	for(int i=len-1; i; --i) ct[i] = ct[i<<1] + ct[i<<1|1];
	for(int i=0; i<=len; ++i) proc(i, 1);
}

int swap_seats(int a, int b) {
	for(int i=1; i<len*2; ++i) std::cout << dt[i] << " \n"[i==len*2-1];
	for(int i=1; i<len*2; ++i) std::cout << mn[i] << " \n"[i==len*2-1];
	for(int i=1; i<len*2; ++i) std::cout << ct[i] << " \n"[i==len*2-1];
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
	for(int i=1; i<len*2; ++i) std::cout << dt[i] << " \n"[i==len*2-1];
	for(int i=1; i<len*2; ++i) std::cout << mn[i] << " \n"[i==len*2-1];
	for(int i=1; i<len*2; ++i) std::cout << ct[i] << " \n"[i==len*2-1];
	return ct[1];
}
