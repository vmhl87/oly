#include <iostream>

#include "wall.h"

struct range{
	int min, max, active;
	void pushup(int h){
		if(h > min) min = h;
		if(h > max) max = h;
	}
	void pushdown(int h){
		if(h < min) min = h;
		if(h < max) max = h;
	}
	void constrain(range r){
		pushup(r.min);
		pushdown(r.max);
	}
	void set() { min = 0, max = 100001; }
};

const int bsz = 1024;

range a[2000000];
range b[2000];

void push(int i){
	if(b[i].active){
		for(int j=0; j<bsz; ++j) a[j+i*bsz].constrain(b[i]);
		b[i].set();
		b[i].active = 0;
	}
}

void set_min(int h, int l, int r){
#ifdef debug
std::cout << "pushup " << h << " (" << l << ' ' << r << ")\n";
#endif
	if(l/bsz == r/bsz){
		push(l/bsz);
		for(int i=l; i<=r; ++i) a[i].pushup(h);
	}else{
		push(l/bsz), push(r/bsz);
		for(int i=l; i/bsz==l/bsz; ++i) a[i].pushup(h);
		for(int i=1+(l/bsz); i<r/bsz; ++i) b[i].pushup(h), b[i].active = 1;
		for(int i=r; i/bsz==r/bsz; --i) a[i].pushup(h);
	}
}

void set_max(int h, int l, int r){
#ifdef debug
std::cout << "pushdown " << h << " (" << l << ' ' << r << ")\n";
#endif
	if(l/bsz == r/bsz){
		push(l/bsz);
		for(int i=l; i<=r; ++i) a[i].pushdown(h);
	}else{
		push(l/bsz), push(r/bsz);
		for(int i=l; i/bsz==l/bsz; ++i) a[i].pushdown(h);
		for(int i=1+(l/bsz); i<r/bsz; ++i) b[i].pushdown(h), b[i].active = 1;
		for(int i=r; i/bsz==r/bsz; --i) a[i].pushdown(h);
	}
}

void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[]){
	for(int i=0; i*bsz<n; ++i) b[i].set();

	for(int i=0; i<k; ++i){
		if(op[i]&1){
			set_min(height[i], left[i], right[i]);
		}else{
			set_max(height[i], left[i], right[i]);
		}

#ifdef debug
for(int i=0; i<n; ++i) std::cout << '[' << a[i].min << ' ' << a[i].max << ']' << " \n"[i==n-1];
for(int i=0; i*bsz<n; ++i) std::cout << "  [" << b[i].active << ' ' << b[i].min << ' ' << b[i].max << "]  " << " \n"[i==4];
std::cout << '\n';
#endif
	}

	for(int i=0; i*bsz<n; ++i) push(i);
#ifdef debug
for(int i=0; i<n; ++i) std::cout << '[' << a[i].min << ' ' << a[i].max << ']' << " \n"[i==n-1];
for(int i=0; i*bsz<n; ++i) std::cout << "  [" << b[i].active << ' ' << b[i].min << ' ' << b[i].max << "]  " << " \n"[i==4];
std::cout << '\n';
#endif
	for(int i=0; i<n; ++i) finalHeight[i] = a[i].min;
}
