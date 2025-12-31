#include <iostream>
#include <array>
#include <map>

const int N = 1e3;

std::array<int, 2> t[N*2];
int a[N], n;

int b[N][N];

std::array<int, 2> merge(std::array<int, 2> a, std::array<int, 2> b){
	if(a[0] > b[1]) return a;
	if(b[0] > a[1]) return b;
	if(a[1] > b[1]) return {b[1], a[1]};
	return {a[1], b[1]};
}

std::array<int, 2> max(int l, int r){
	std::array<int, 2> res = {-1, -1};
	for(l+=n, r+=n+1; l<r; l/=2, r/=2){
		if(l&1) res = merge(res, t[l++]);
		if(r&1) res = merge(res, t[--r]);
	}
	return res;
}

int main(){
	int q; std::cin >> n >> q;
	for(int i=0; i<n; ++i) std::cin >> a[i];

	for(int i=0; i<n; ++i) t[i+n] = {-1, a[i]};
	for(int i=n-1; i; --i) t[i] = merge(t[i*2], t[i*2+1]);
	
	std::map<int, int> idx;
	for(int i=0; i<n; ++i) idx[a[i]] = i;

	for(int i=0; i<n; ++i){
		++b[i][0];
		int lp = i-1, rp = i+1;

		for(int j=1; j<n; ++j){
			if(lp < 0){
				++b[rp][j];
				++rp;
			}else if(rp >= n){
				++b[lp][j];
				--lp;
			}else{
				if(a[lp] < a[rp]){
					++b[lp][j];
					--lp;
				}else{
					++b[rp][j];
					++rp;
				}
			}
		}
	}

	while(q--){
		int p, k; std::cin >> p >> k, --p, --k;
		if(!k) { std::cout << 1 << ' ' << b[p][k] << '\n'; continue; }
		int res = 0;

		// consider either range [p-k, p] or [p, p+k]

		// range [p-k, p]
		if(p-k == 0){
			for(int i=p-k; i<p; ++i)
				if(max(p-k, i-1)[1] < max(i+1, p)[1]) ++res;

		}else if(p-k > 0){
			auto M = max(p-k, p);

			if(a[p-k-1] > M[1]){
				for(int i=p-k; i<p; ++i)
					if(max(p-k, i-1)[1] < max(i+1, p)[1]) ++res;
			
			}else if(a[p-k-1] > M[0]){
				int i = idx[M[1]];
				if(max(p-k, i-1)[1] < max(i+1, p)[1]) ++res;
			}
		}

		// range [p, p+k]
		if(p+k == n-1){
			for(int i=p+1; i<=p+k; ++i)
				if(max(i+1, p+k)[1] < max(p, i-1)[1]) ++res;
	
		}else if(p+k < n-1){
			auto M = max(p, p+k);

			if(a[p+k+1] > M[1]){
				int i = idx[M[1]]; res += p+k-i;
				if(max(i+1, p+k)[1] < max(p, i-1)[1]) ++res;

			}else if(a[p+k+1] > M[0]){
				int i = idx[M[1]];
				if(max(i+1, p+k)[1] < max(p, i-1)[1]) ++res;
			}
		}

		std::cout << res << ' ' << b[p][k] << '\n';
	}
}
