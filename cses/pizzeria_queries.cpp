#include <iostream>

const int N = 2e5;

int a[N], t1[N*2], t2[N*2];

int main(){
	int n, q; std::cin >> n >> q;
	for(int i=0; i<n; ++i) std::cin >> a[i];

	for(int i=0; i<n; ++i) t1[i+n] = a[i] + i;
	for(int i=n-1; i; --i) t1[i] = std::min(t1[i*2], t1[i*2+1]);

	for(int i=0; i<n; ++i) t2[i+n] = a[i] - i;
	for(int i=n-1; i; --i) t2[i] = std::min(t2[i*2], t2[i*2+1]);

	while(q--){
		int t; std::cin >> t;
		
		if(t&1){
			int k, x; std::cin >> k >> x, --k;
			t1[k+n] += x - a[k];
			t2[k+n] += x - a[k];
			a[k] = x;

			for(int i=(k+n)/2; i; i/=2)
				t1[i] = std::min(t1[i*2], t1[i*2+1]),
					t2[i] = std::min(t2[i*2], t2[i*2+1]);
		}else{
			int k; std::cin >> k, --k;

			int best = a[k];

			for(int l=k+n, r=n+n; l<r; l/=2, r/=2){
				if(l&1) best = std::min(best, t1[l++] - k);
				if(r&1) best = std::min(best, t1[--r] - k);
			}

			for(int l=n, r=k+n; l<r; l/=2, r/=2){
				if(l&1) best = std::min(best, t2[l++] + k);
				if(r&1) best = std::min(best, t2[--r] + k);
			}

			std::cout << best << '\n';
		}
	}
}
