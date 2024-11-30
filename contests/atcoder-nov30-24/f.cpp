#include <algorithm>
#include <iostream>
#include <array>

const int N = 2e5;

std::array<int, 4> a[N];
int res[N], h, w;

namespace s{
	bool lz[N*4];
	int t[N*4];

	void build(int i, int l, int r){
		if(l == r) t[i] = h;
		else build(i*2, l, (l+r)/2),
			build(i*2+1, 1+(l+r)/2, r),
				t[i] = h;
	}

	void push(int i){
		if(lz[i]){
			t[i*2] = t[i];
			t[i*2+1] = t[i];
			lz[i*2] = 1;
			lz[i*2+1] = 1;
			lz[i] = 0;
		}
	}

	int rmq(int i, int l, int r, int lb, int rb){
		if(lb > rb) return N;
		if(l == lb && r == rb) return t[i];
		push(i);
		int m = (l+r)/2;
		return std::min(
				rmq(i*2, l, m, lb, std::min(rb, m)),
				rmq(i*2+1, m+1, r, std::max(lb, m+1), rb));
	}

	void set(int i, int l, int r, int lb, int rb, int v){
		if(lb > rb) return;
		if(l == lb && r == rb) t[i] = v, lz[i] = 1;
		else{
			push(i);
			int m = (l+r)/2;
			set(i*2, l, m, lb, std::min(rb, m), v),
			set(i*2+1, m+1, r, std::max(lb, m+1), rb, v);
			t[i] = std::min(t[i*2], t[i*2+1]);
		}
	}
}

void build(){
	s::build(1, 0, w);
}

int rmq(int l, int r){
	return s::rmq(1, 0, w, l, r-1);
}

void set(int l, int r, int i){
	s::set(1, 0, w, l, r-1, i);
}

int main(){
	int n; std::cin >> h >> w >> n;

	for(int i=0; i<n; ++i){
		std::cin >> a[i][0] >> a[i][1] >> a[i][2];
		--a[i][1], a[i][2] += a[i][1];
		a[i][3] = i;
	}

	std::sort(a, a+n, std::greater());

	//for(int i=0; i<n; ++i) std::cout << a[i][0] << '\n';
	
	build();
	
	for(int i=0; i<n; ++i){
		res[a[i][3]] = rmq(a[i][1], a[i][2]);
		set(a[i][1], a[i][2], res[a[i][3]]-1);
	}

	for(int i=0; i<n; ++i) std::cout << res[i] << '\n';
}
