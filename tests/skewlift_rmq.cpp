#include <iostream>
#include <array>

const int N = 2e5 + 1;

std::array<int, 2> j[N];
int a[N], back[N];

void build(int i){
	if(i-1+j[j[i-1][0]][0] == 2*j[i-1][0]){
		j[i] = {
			j[j[i-1][0]][0],
			std::min(a[i],
					std::min(j[i-1][1],
						j[j[i-1][0]][1]))
		},
			back[i-1] = i,
			back[j[i-1][0]] = i;
	}else j[i] = {i-1, a[i]};
}

void rebuild(int i){
	build(i);
	if(back[i]) rebuild(back[i]);
}

int range(int l, int r){
	int res = a[l];
	while(l<r){
		if(j[r][0] >= l)
			res = std::min(res, j[r][1]),
				r = j[r][0];
		else res = std::min(res, a[r--]);
	}
	return res;
}

int main(){
	int n, q; std::cin >> n >> q;
	for(int i=0; i<n; ++i) std::cin >> a[i+1];

	for(int i=1; i<=n; ++i) build(i);

	while(q--){
		int t, x, y; std::cin >> t >> x >> y;

		if(t&1) a[x] = y, rebuild(x);
		else std::cout << range(x, y) << '\n';
	}
}
