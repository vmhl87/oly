#include <iostream>
#include <map>

using ll = long long;
const int N = 2e5;

int a[N];

int main(){
	std::map<int, ll> ct;

	int n; std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> a[i], ++ct[a[i]-i];

	ll res = 0;

	for(int i=0; i<n; ++i){
		--ct[a[i]-i];
		res += ct[-a[i]-i];
	}

	std::cout << res << '\n';
}
