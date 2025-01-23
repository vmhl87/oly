#include <algorithm>
#include <iostream>
#include <array>

const int N = 3e5;
int q, l[N], r[N], t[N*2], res[N];
std::array<int, 2> v[N];

void add(int l, int r){
	for(l+=q, r+=q; l<r; l/=2, r/=2){
		if(l&1) ++t[l++];
		if(r&1) ++t[--r];
	}
}

int get(int i){
	int res = 0;
	for(i+=q; i; i/=2) res += t[i];
	return res;
}

int bound(int i){
	int res = q;
	for(int s=1<<18; s; s/=2)
		if(res>=s && get(res-s)>=i)
			res -= s;
	return res;
}

int main(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i)
		std::cin >> l[i] >> r[i];

	std::cin >> q;
	for(int i=0; i<q; ++i)
		std::cin >> v[i][0], v[i][1] = i;
	std::sort(v, v+q);

	for(int i=0; i<q; ++i)
		t[i+q] = v[i][0];

	for(int i=0; i<n; ++i)
		add(bound(l[i]), bound(r[i]+1));

	for(int i=0; i<q; ++i)
		res[v[i][1]] = get(i);

	for(int i=0; i<q; ++i)
		std::cout << res[i] << '\n';
}
