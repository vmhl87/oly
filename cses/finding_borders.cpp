#include <iostream>
#include <string>

using ll = long long;
const int maxn = 1e6 + 1,
	  m = 1e9 + 7,
	  p = 200003;

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

	small[0] = 1, big[0] = 1;
	for(int i=0; i<1024; ++i) small[i+1] = small[i]*p % m;
	for(int i=1; i<1024; ++i) big[i] = big[i-1]*small[1024] % m;

	for(int i=1; i<n; ++i) if(same(0, n-i, i))
		std::cout << i << ' ';
	std::cout << '\n';
}
