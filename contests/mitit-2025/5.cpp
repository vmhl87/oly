#include <iostream>
#include <set>

const int N = 2e5;

int a[N], c[N+1], t;
std::set<int> v;

int main(){
	int n, q; std::cin >> n >> q;
	for(int i=0; i<n; ++i) std::cin >> a[i];

	for(int i=1; i<=n; ++i) v.insert(i);

	for(int i=0; i<n; ++i)
		if(!(c[a[i]]++)) ++t, v.erase(a[i]);

	while(q--){
		int f, x, y; std::cin >> f >> x >> y;

		if(1&f){
			--x;
			if(!(--c[a[x]])) --t, v.insert(a[x]);
			a[x] = y;
			if(!(c[a[x]]++)) ++t, v.erase(a[x]);
		}else{
			if(t == n){
				if(x == 1) std::cout << a[n-1] << '\n';
				else std::cout << a[0] << '\n';
			}else{
				std::cout << (*v.begin()) << '\n';
			}
		}
	}
}
