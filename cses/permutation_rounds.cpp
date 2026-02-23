#include <iostream>
#include <set>

using ll = long long;
const int N = 2e5 + 1, m = 1e9 + 7;

bool sieve[N], t[N];
int a[N];

int main(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> a[i], --a[i];

	std::set<int> c;

	for(int i=0; i<n; ++i) if(!t[i]){
		int len = 1;
		for(int j=a[i]; j!=i; j=a[j]) ++len, t[j] = 1;
		c.insert(len);
	}

	for(int i=2; i<=n; ++i) sieve[i] = 1;
	for(int i=2; i<=n; ++i) if(sieve[i])
		for(int j=i+i; j<=n; j+=i) sieve[j] = 0;

	ll res = 1;

	for(int i=2; i<=n; ++i) if(sieve[i]){
		int max = 0; ll p = 1;

		for(int j : c){
			int v = 1; ll r = 1;
			while(j%i == 0) ++v, r = r*i % m, j /= i;
			if(v > max) max = v, p = r;
		}

		res = res*p % m;
	}

	std::cout << res << '\n';
}
