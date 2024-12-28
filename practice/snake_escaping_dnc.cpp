#include <algorithm>
#include <iostream>

int *a[21], d[1<<21];

using ll = long long;
const ll X = (1<<22) - 1;

int res[1000000];
ll b[1000000];

void dfs(int l, int r, int d, int s){
	if(!s)
		for(; l<r; ++l) res[b[l] & X] = a[d][0];

	else{
		int s1 = r, s2 = r;

		for(int i=r-1; i>=l; --i){
			if(((b[i] >> (60-d*2)) & 3) == 2) s2 = s1 = i;
			if(((b[i] >> (60-d*2)) & 3) == 1) s1 = i;
		}

		if(l != s1){
			for(int i=0; i<s; ++i)
				a[d+1][i] = a[d][i];
			dfs(l, s1, d+1, s/2);
		}

		if(s1 != s2){
			for(int i=0; i<s; ++i)
				a[d+1][i] = a[d][i+s];
			dfs(s1, s2, d+1, s/2);
		}

		if(s2 != r){
			for(int i=0; i<s; ++i)
				a[d+1][i] = a[d][i] + a[d][i+s];
			dfs(s2, r, d+1, s/2);
		}
	}
}

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int l, q; std::cin >> l >> q;

	a[0] = d;
	for(int s=1<<l, p=1; s; ++p, s/=2)
		a[p] = a[p-1]+s;

	for(int i=0; i<1<<l; ++i){
		char c; std::cin >> c;
		a[0][i] = c-'0';
	}

	for(int i=0; i<q; ++i){
		b[i] |= i;
		for(int j=0; j<l; ++j){
			char c; std::cin >> c;
			ll m = c == '?' ? 2 : c - '0';
			b[i] |= m << (60-j*2);
		}
	}

	std::sort(b, b+q);

	dfs(0, q, 0, 1<<(l-1));

	for(int i=0; i<q; ++i) std::cout << res[i] << '\n';
}
