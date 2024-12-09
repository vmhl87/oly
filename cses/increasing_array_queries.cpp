#include <algorithm>
#include <iostream>
#include <array>

using ll = long long;
const int N = 2e5;

std::array<int, 3> r[N];
ll res[N];
int a[N];

int main(){
	int n, q; std::cin >> n >> q;
	for(int i=0; i<n; ++i) std::cin >> a[i];
	for(int i=0; i<q; ++i){
		std::cin >> r[i][1] >> r[i][0];
		r[i][2] = i;
	}

	std::sort(r, r+q);
}
