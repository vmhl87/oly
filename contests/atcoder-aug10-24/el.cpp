#include <iostream>

using LL = long long;

int p[200000][2];

int main(){
	int n, d; std::cin >> n >> d;
	for(int i=0; i<n; ++i) std::cin >> p[i][0] >> p[i][1];

	int lx = p[0][0], rx = p[0][0], ly = p[0][1], ry = p[0][1];

	for(int i=1; i<n; ++i){
		lx = std::min(lx, p[i][0]);
		rx = std::max(rx, p[i][0]);
		ly = std::min(ly, p[i][1]);
		ry = std::max(ry, p[i][1]);
	}

	for(int i=0; i<100; ++i){
		for(int j=0; j<100; ++j){
			int sum = 0;
			for(int k=0; k<n; ++k)
				sum += std::abs(i-p[k][0]) + std::abs(j-p[k][1]);
			printf("%c%c", "_#"[sum<=d], " \n"[j==99]);
		}
	}

	for(int i=1; i<n; ++i){
		d -= std::abs(p[0][0] - p[i][0]);
		d -= std::abs(p[0][1] - p[i][1]);
	}

	if(d<0) { std::cout << 0 << '\n'; return 0; }

	d /= n;

	rx -= lx, ++rx;
	ry -= ly, ++ry;

	LL ret = (LL)rx * (LL)ry;
	ret += 2LL * (LL)d * (LL)rx;
	ret += 2LL * (LL)d * (LL)ry;
	if(d) ret += 2LL * ((LL)d * ((LL)d - 1LL));

	std::cout << ret << '\n';
}
