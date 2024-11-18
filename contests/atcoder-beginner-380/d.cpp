#include <iostream>
#include <string>

using ll = long long;

int main(){
	std::string s; std::cin >> s;
	ll n = s.length();

	int k; std::cin >> k;

	for(int i=0; i<k; ++i){
		ll x; std::cin >> x, --x;
		ll a = x/n, b = x%n;

		char res = s[b];

		int ct = 0;
		for(; a; a/=2) if(a&1) ++ct;

		if(ct & 1){
			if(res >= 'a' && res <= 'z')
				res += 'A' - 'a';
			else res += 'a' - 'A';
		}

		std::cout << res << " \n"[i==k-1];
	}
}
