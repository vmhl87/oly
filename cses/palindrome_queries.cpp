#include <iostream>
#include <string>

using ll = long long;
const int maxn = 2e5,
	  m = 1e9 + 7,
	  p = 200003;

ll big[1024], small[1025];

ll pow(int i) { return big[i>>10] * small[i&1023] % m; }

ll h1[maxn*2], h2[maxn*2];
int n = 2e5;

void set1(int i, ll v){
	h1[i+n] = v;
	for(i=(i+n)/2; i; i/=2)
		h1[i] = (h1[2*i] + h1[2*i+1] % m);
}

void set2(int i, ll v){
	h2[i+n] = v;
	for(i=(i+n)/2; i; i/=2)
		h2[i] = (h2[2*i] + h2[2*i+1] % m);
}

ll get1(int l, int r){
	ll res = 0;
	for(l += n, r += n; l < r; l /= 2, r /= 2){
		if(l&1) res = (res + h1[l++]) % m;
		if(r&1) res = (res + h1[--r]) % m;
	}
	return res;
}

ll get2(int l, int r){
	ll res = 0;
	for(l += n, r += n; l < r; l /= 2, r /= 2){
		if(l&1) res = (res + h2[l++]) % m;
		if(r&1) res = (res + h2[--r]) % m;
	}
	return res;
}

bool same(int l, int r){
	ll s1 = get1(l, r+1), s2 = get2(n-r-1, n-l);
	return (s1*pow(n-r-1) % m) == (s2*pow(l) % m);
}

void upd(int i, char v){
	set1(i, v*pow(i)%m);
	set2(n-i-1, v*pow(n-i-1)%m);
}

int main(){
	int n, q; std::cin >> n >> q;
	std::string a; std::cin >> a;
	n = a.length();

	++big[0], ++small[0];
	for(int i=0; i<1024; ++i) small[i+1] = small[i]*p % m;
	for(int i=1; i<1024; ++i) big[i] = big[i-1]*small[1024] % m;

	for(int i=0; i<n; ++i) upd(i, (ll)a[i]);

	while(q--){
		int x, y; std::cin >> x >> y;

		if(x&1){
			char z; std::cin >> z;
			upd(y-1, z);
		}else{
			int z; std::cin >> z;
			std::cout << (same(y-1, z-1) ? "YES" : "NO") << '\n';
		}
	}
}
