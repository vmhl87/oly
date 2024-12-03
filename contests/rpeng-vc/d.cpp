#include <algorithm>
#include <iostream>
#include <array>

const int N = 5e4;

std::array<int, 2> e[N*2];

int rmq[(int)2e6], n;

void set(int i, int v){
	rmq[i = i+1e6] = v;
	for(i/=2; i; i/=2)
		rmq[i] = std::min(rmq[i*2], rmq[i*2+1]);
}

bool v[(int)2e6+1];

int main(){
	freopen("stampede.in", "r", stdin);
	freopen("stampede.out", "w", stdout);

	std::cin >> n;

	for(int i=0; i<n; ++i){
		int x, y, r; std::cin >> x >> y >> r;
		x = -x, --y;
		e[i*2] = {x*r, -1-y};
		e[i*2+1] = {(x-1)*r, y};
	}

	std::sort(e, e+n+n);

	for(int i=0; i<2e6; ++i) rmq[i] = 2e6;

	int last = e[0][0];

	for(int i=0; i<n*2; ++i){
		if(e[i][0] != last) v[rmq[1]] = 1;
		last = e[i][0];

		if(e[i][1] < 0) set(-1-e[i][1], 2e6);
		else set(e[i][1], e[i][1]);
	}

	v[rmq[1]] = 1;

	int res = 0;

	for(int i=0; i<2e6; ++i) if(v[i]) ++res;

	std::cout << res << '\n';
}
