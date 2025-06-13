#include <iostream>

const int N = 5e5;

int h[N], r[N], dp[N], n, tree[N*2];

int range(int l, int r){
	l = std::max(l, 0);
	r = std::min(r, n);
	int res = -1;
	for(l += n, r += n; l < r; l /= 2, r /= 2){
		if(l&1) res = std::max(res, tree[l++]);
		if(r&1) res = std::max(res, tree[--r]);
	}
	return res;
}

void add(int i){
	tree[r[i]+n] = dp[i];
	for(i=(r[i]+n)/2; i; i/=2)
		tree[i] = std::max(tree[i*2], tree[i*2+1]);
}

int main(){
	int d, R; std::cin >> n >> d >> R;
	for(int i=0; i<n; ++i) std::cin >> h[i], r[--h[i]] = i;
	for(int i=0; i<n*2; ++i) tree[i] = -1;

	for(int i=1; i<n; ++i){
		if(i >= d) add(i-d);
		dp[i] = 1 + range(r[i]-R, r[i]+R+1);
	}

	// for(int i=0; i<n; ++i) std::cout << dp[i] << " \n"[i==n-1];

	int res = dp[0];
	for(int i=1; i<n; ++i) res = std::max(res, dp[i]);
	std::cout << res << '\n';
}
