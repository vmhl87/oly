#include <iostream>

int a[200000], up[200000], down[200000];

int seq[200000], sz;

void test(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> a[i];

	sz = 0;
	for(int i=0; i<n; ++i){
		int x = sz;
		for(int j=1<<18; j; j/=2)
			if(x-j >= 0 && seq[x-j] >= a[i])
				x -= j;
		seq[x] = a[i]; if(x == sz) ++sz;
		up[i] = sz;
	}

	sz = 0;
	for(int i=n-1; i>=0; --i){
		int x = sz;
		for(int j=1<<18; j; j/=2)
			if(x-j >= 0 && seq[x-j] >= a[i])
				x -= j;
		seq[x] = a[i]; if(x == sz) ++sz;
		down[i] = sz;
	}

	int best = 0;

	for(int i=0; i<n; ++i) if(up[i] > 1 && down[i] > 1)
		best = std::max(best, up[i]+down[i]-1);

	std::cout << best << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
