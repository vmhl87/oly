#include <iostream>

const int N = 2e5 + 1;

int jl[N], j[N];
int a[N], back[N];

void upd(int i){
	if(jl[i] != i-1) j[i] =
			std::min(a[i],
					std::min(j[i-1],
						j[jl[i-1]]));
	else j[i] = a[i];
}

void build(int i){
	if(i-1+jl[jl[i-1]] == 2*jl[i-1])
		jl[i] = jl[jl[i-1]],
			back[jl[i-1]] = i,
			back[i-1] = i;
	else jl[i] = i-1;
	upd(i);
}

void rebuild(int i){
	while(i) upd(i), i = back[i];
}

int range(int l, int r){
	int res = a[l];
	while(l <= r){
		if(jl[r] >= l)
			res = std::min(res, j[r]),
				r = jl[r];
		else res = std::min(res, a[r--]);
	}
	return res;
}

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int n, q; std::cin >> n >> q;
	for(int i=0; i<n; ++i) std::cin >> a[i+1];

	for(int i=1; i<=n; ++i) build(i);

	while(q--){
		int t, x, y; std::cin >> t >> x >> y;

		if(t&1) a[x] = y, rebuild(x);
		else std::cout << range(x, y) << '\n';
	}
}
