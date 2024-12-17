#include <algorithm>
#include <iostream>
#include <array>
#include <set>

const int N = 1e5;

int a[N], b[N][4], n;

int idx(int i){
	int res = n;
	for(int s=1<<17; s; s/=2)
		if(res-s >= 0 && a[res-s] >= i)
			res -= s;
	return res;
}

std::array<int, 2> add[N], sub[N];

void test(){
	int k; std::cin >> n >> k;
	for(int i=0; i<n; ++i) std::cin >> a[i];
	for(int i=0; i<k; ++i) std::cin >> b[i][0] >> b[i][1] >> b[i][2];

	std::sort(a, a+n);

	for(int i=0; i<k; ++i){
		++b[i][1];
		for(int j=0; j<2; ++j)
			b[i][j] = idx(b[i][j]);
		add[i] = {b[i][0], i};
		sub[i] = {b[i][1], i};
		b[i][3] = b[i][1]-b[i][0]-b[i][2];
	}

	std::sort(add, add+k);
	std::sort(sub, sub+k);

	int p1 = 0, p2 = 0;

	std::set<std::array<int, 2>> active;
	int res = 0;

	for(int i=0; i<n; ++i){
		while(p1 < k && add[p1][0] == i){
			active.insert({res + b[add[p1][1]][3], add[p1][1]});
			b[add[p1][1]][3] += res;
			++p1;
		}
		while(p2 < k && sub[p2][0] == i){
			active.erase({b[sub[p2][1]][3], sub[p2][1]});
			++p2;
		}

		if(active.size()){
			int j = (*active.begin())[0];
			if(j > res) ++res;
		}else ++res;
	}

	std::cout << res << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
