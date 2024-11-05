#include <iostream>
#include <string>

using ll = long long;
const int maxn = 1e6 + 1,
	  m = 1e9 + 7,
	  p = 200003;

bool sieve[maxn], work[maxn];
ll hash[maxn];

ll big[1024], small[1025];

ll pow(int i){
	return big[i>>10] * small[i&1023] % m;
}

ll section(int l, int r){
	ll res = hash[r] - hash[l];
	res = res % m;
	if(res < 0) res += m;
	return res;
}

bool same(int a, int b, int len){
	return (section(a, a+len) * pow(b-a) % m) == section(b, b+len);
}

int main(){
	std::string a; std::cin >> a;
	int n = a.length();

	ll part = 1;

	for(int i=0; i<n; ++i)
		hash[i+1] = (hash[i] + part*a[i] % m) % m,
			part = part*p % m;

	small[0] = 1;
	for(int i=0; i<1024; ++i)
		small[i+1] = small[i]*p % m;

	big[0] = 1;
	for(int i=1; i<1024; ++i)
		big[i] = big[i-1]*small[1024] % m;

	for(int i=1; i<=n; ++i) sieve[i] = 1;

	for(int i=2; i<=n; ++i) if(sieve[i])
		for(int j=i+i; j<=n; j+=i) sieve[j] = 0;

	for(int i=1; i<=n; ++i) if(sieve[i]){
		bool works = 1;
		for(int j=i; j<n; j+=i)
			works &= same(0, j, std::min(i, n-j));
		if(works) for(int j=i; j<=n; j+=i) work[j] = 1;
	}

	for(int i=1; i<=n; ++i) if(work[i]) std::cout << i << ' ';
	std::cout << '\n';
}
