#include <algorithm>
#include <iostream>
#include <random>
#include <chrono>

#define stress 1

const int N = 2e5;

int a[N], r[N], c[N];
bool b[N];

#ifdef stress
int d[N];
#endif

void test(){
	int n; std::cin >> n;
#ifdef stress
	for(int i=0; i<n; ++i) a[i] = i;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);
    std::shuffle(a, a+n, rng);
	for(int i=n-1; i>=0; --i){
		int j = 0;
		while(a[j] != i) ++j;
		while(j && a[j] < a[j-1])
			std::swap(a[j], a[j-1]), --j;
	}
	for(int i=0; i<n; ++i) r[a[i]] = i, b[i] = 0, c[i] = -1, std::cout << a[i]+1 << " \n"[i==n-1];
#else
	for(int i=0; i<n; ++i) std::cin >> a[i], --a[i], r[a[i]] = i, b[i] = 0, c[i] = -1;
#endif

	for(int i=0; i<n; ++i){
		if(r[i] && a[r[i]-1] > i){  // houston, we have a problem
			bool v = 0;
			int mins = i;

			for(int j=r[i]-1; j>=0; --j){
				if(a[j] < mins && !b[j]){
					c[i] = a[j], b[j] = 1;
					v = 1; break;
				}
				if(c[a[j]] != -1) mins = std::min(mins, c[a[j]]);
				if(!b[j]) mins = std::min(mins, a[j]);
			}

			if(!v){
				std::cout << -1 << '\n';
				return;
			}
		}
	}

	for(int i=0; i<n; ++i){
		if(c[a[i]] != -1) std::cout << c[a[i]]+1 << ' ';
		if(!b[i]) std::cout << a[i]+1 << ' ';
	}

	std::cout << '\n';

#ifdef stress
	int *p = d;

	for(int i=0; i<n; ++i){
		if(c[a[i]] != -1) *(p++) = c[a[i]];
		if(!b[i]) *(p++) = a[i];
	}

	if(p != d+n) std::cout << "mismatched length\n";
	else{
		for(int i=n-1; i>=0; --i){
			int j = 0;
			while(d[j] != i) ++j;
			while(j && d[j] < d[j-1])
				std::swap(d[j], d[j-1]), --j;
		}
		for(int i=0; i<n; ++i) std::cout << d[i]+1 << " \n"[i==n-1];
	}
#endif
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
