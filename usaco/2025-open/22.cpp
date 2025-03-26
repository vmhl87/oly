#include <iostream>
#include <map>

const int N = 2e5;

int a[N], ct[N], t[N*2], t2[N*2+2];

int n;

int rmq(int l, int r){
	int res = 0;
	for(l += n+1, r += n+1; l<r; l/=2, r/=2){
		if(l&1) res = std::max(res, t2[l++]);
		if(r&1) res = std::max(res, t2[--r]);
	}
	return res;
}

int main(){
	int q; std::cin >> n >> q;
	for(int i=0; i<n; ++i) std::cin >> a[i], --a[i];

	for(int i=0; i<n; ++i) ++ct[a[i]];
	for(int i=0; i<n; ++i) t[a[i]+n] = ct[a[i]];
	for(int i=n-1; i; --i) t[i] = std::max(t[i*2], t[i*2+1]);

	while(q--){
		{
			int i, x; std::cin >> i >> x, --i, --x;
			--ct[a[i]], t[a[i]+n] = ct[a[i]];
			for(int j=(a[i]+n)/2; j; j/=2) t[j] = std::max(t[j*2], t[j*2+1]);
			a[i] = x;
			++ct[a[i]], t[a[i]+n] = ct[a[i]];
			for(int j=(a[i]+n)/2; j; j/=2) t[j] = std::max(t[j*2], t[j*2+1]);
		};

		int max = t[1], best = 0;

		for(int i=0; i<n*2+2; ++i) t2[i] = 0;

		for(int i=n-2; i>=0; --i){
			if(!t2[ct[i+1]+n+1] && ct[i+1]){
				t2[ct[i+1]+n+1] = i+1;
				for(int j=(ct[i+1]+n+1)/2; j; j/=2)
					t2[j] = std::max(t2[j*2], t2[j*2+1]);
			}
			if(ct[i]) best = std::max(best, rmq(max-ct[i], n+1)-i);
		}

		std::cout << best << '\n';
	}
}
