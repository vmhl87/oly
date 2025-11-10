#include <iostream>
#include <vector>

const int N = 1<<15;

std::vector<int> cycle[N];
int v[N], p[N], P[N];

int a[N], b[N];

void test(){
	int n, q; std::cin >> n >> q;

	for(int i=0; i<n; ++i){
		cycle[i].clear();
		v[i] = -1, p[N] = 0;
	}

	for(int i=0, j; i<n; ++i) std::cin >> j, a[j-1] = i;
	for(int i=0; i<n; ++i) std::cin >> P[i], --P[i];

	for(int i=0; i<n; ++i) if(v[i] == -1){
		v[i] = i, p[i] = cycle[i].size();
		cycle[i].push_back(i);

		for(int j=P[i]; j!=i; j=P[j]){
			v[j] = i, p[j] = cycle[i].size();
			cycle[i].push_back(j);
		}
	}

	int k = 0;

	while(q--){
		int K; std::cin >> K, k += K;

		if(n == 1){
			std::cout << 1 << '\n';
			continue;
		}

		auto pos = [&] (int i) {
			int c = v[a[i]];
			int sz = cycle[c].size();
			int idx = (p[a[i]]+k)%sz;
			return cycle[c][idx];
		};

		int l = 0, r = n;

		for(int i=0; i<n; ++i){
			// std::cout << l << ' ' << r << ' ' << i+1 << '\n';
			int j = pos(i);
			if(j < l || j >= r) continue;
			if(l == r-1){
				std::cout << i+1 << '\n';
				break;
			}
			int m = (l+r)/2;
			if(j < m) l = m;
			else r = m;
			// std::cout << '-' << l << ' ' << r << '\n';
		}
	}
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}

// [ 4 1 3 2 ] 1:
// [ 3 2 ] 2:
// [ 3 ]
//
// 0..4 m: 2
// 2..4
// 2..3
