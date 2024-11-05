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

int main(){
	std::string a, b; std::cin >> a >> b;

	ll part = 1;

	for(int i=0; i<a.length(); ++i)
		hash[i+1] = (hash[i] + part*a[i] % m) % m,
			part = part*p % m;

	ll match = 0;
	part = 1;

	for(char c : b)
		match = (match + part*c) % m,
			  part = part*p % m;

	small[0] = 1;
	for(int i=0; i<1024; ++i)
		small[i+1] = small[i]*p % m;

	big[0] = 1;
	for(int i=1; i<1024; ++i)
		big[i] = big[i-1]*small[1024] % m;

	int res = 0;

	for(int i=0; i+b.length()<=a.length(); ++i){
		ll diff = match * pow(i) % m;
		if((hash[i]+diff) % m == hash[i+b.length()])
			++res;
	}

	std::cout << res << '\n';
}
