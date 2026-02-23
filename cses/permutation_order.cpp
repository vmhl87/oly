#include <algorithm>
#include <iostream>
#include <cassert>
#include <vector>

using ll = long long;

ll fact[21];
int a[21];

int main(){
	fact[0] = 1;
	for(int i=1; i<21; ++i) fact[i] = fact[i-1] * i;

	int t; std::cin >> t;

	while(t--){
		int x, n; std::cin >> x >> n;

		if(x == 1){
			ll k; std::cin >> k, --k;
			std::vector<int> v(n);
			for(int i=0; i<n; ++i) v[i] = i+1;

			for(int i=0; i<n; ++i){
				ll index = k/fact[n-i-1];
				assert(index >= 0 && index < v.size());
				std::cout << v[index] << " \n"[i==n-1];
				v.erase(v.begin() + index);
				k -= index*fact[n-i-1];
			}

		}else{
			for(int i=0; i<n; ++i) std::cin >> a[i];
			std::vector<int> v(n);
			for(int i=0; i<n; ++i) v[i] = i+1;

			ll res = 1;

			for(int i=0; i<n; ++i){
				int index = std::find(v.begin(), v.end(), a[i]) - v.begin();
				assert(index >= 0 && index < v.size());
				res += index*fact[n-i-1];
				v.erase(v.begin() + index);
			}

			std::cout << res << '\n';
		}
	}
}
