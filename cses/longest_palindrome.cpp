#include <iostream>
#include <string>

using ll = long long;
const int maxn = 1e6 + 1,
	  m = 1e9 + 7,
	  p = 2e5 + 3;

std::string s;
int n;

ll big[1024], small[1025];

ll pow(int i){
	return big[i>>10]*small[i&1023] % m;
}

ll hf[maxn], hr[maxn];

ll sect(ll *h, int l, int r){
	ll res = (h[r] - h[l]) % m;
	return res + m*(res < 0);
}

bool equiv(int l1, int r1, int l2, int r2){
	/*
	std::cout << "equiv " << l1 << ' ' << r1 << ' ' << l2 << ' ' << r2 << " -> ";
	for(int i=l1, j=r2-1; i<r1; ++i, --j)
		if(s[i] != s[j]){
			std::cout << "0\n";
			return 0;
		}
	std::cout << 1 << '\n';
	return 1;
	*/
	return sect(hf, l1, r1) * pow(n-r2) % m == sect(hr, r2, l2) * pow(l1) % m;
}

int main(){
	std::cin >> s, n = s.length();

	small[0] = 1; big[0] = 1;
	for(int i=0; i<1024; ++i) small[i+1] = small[i]*p % m;
	for(int i=1; i<1024; ++i) big[i] = big[i-1]*small[1024] % m;

	for(int i=0; i<n; ++i)
		hf[i+1] = (hf[i] + s[i]*pow(i)) % m;

	for(int i=n; i; --i)
		hr[i-1] = (hr[i] + s[i-1]*pow(n-i)) % m;

	int best = 1, loc = 0;

	for(int i=0; i<n; ++i){
		int ms = std::min(i+1, n-i);

		for(int j=best; j<=ms; ++j){
			if(equiv(i-j+1, i+1, i, i+j)) best = j, loc = i-j+1;
			else break;
		}
	}

	best = best*2 - 1;

	for(int i=1; i<n; ++i){
		int ms = std::min(i, n-i);

		for(int j=best/2; j<=ms; ++j){
			if(equiv(i-j, i, i, i+j)){
				if(j*2 > best) best = j*2, loc = i-j;
			}else break;
		}
	}

	for(int i=0; i<best; ++i) std::cout << s[loc+i];
	std::cout << '\n';
}
