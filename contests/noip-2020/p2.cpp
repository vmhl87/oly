#include <iostream>
#include <string>

using ll = long long;
const ll p1 = 61, p2 = 200009, m = 1e9+7;

ll h1[2000000], h2[2000000];

ll pow(ll a, int p){
	ll res = 1;
	for(; p; p/=2, a=a*a%m)
		if(p&1) res = res*a % m;
	return res;
}

bool same1(int l1, int r1, int l2, int r2){
	ll d1 = h1[r1] - h1[l1], d2 = h1[r2] - h1[l2];
	d1 = (m + (d1 % m)) % m;
	d2 = (m + (d2 % m)) % m;
	d1 = d1 * pow(p1, l2) % m;
	d2 = d2 * pow(p1, l1) % m;
	return d1 == d2;
}

bool same2(int l1, int r1, int l2, int r2){
	ll d1 = h2[r1] - h2[l1], d2 = h2[r2] - h2[l2];
	d1 = (m + (d1 % m)) % m;
	d2 = (m + (d2 % m)) % m;
	d1 = d1 * pow(p2, l2) % m;
	d2 = d2 * pow(p2, l1) % m;
	return d1 == d2;
}

bool same(int l1, int r1, int l2, int r2){
	return same1(l1, r1, l2, r2) && same2(l1, r1, l2, r2);
}

int ps[2000000];

int sum(int l, int r){
	int res = ps[r] ^ ps[l];
	return __builtin_popcount(res);
}

void test(){
	std::string s; std::cin >> s;

	for(int i=0; i<s.length(); ++i)
		ps[i+1] = ps[i] ^ (1 << (s[i] - 'a'));

	for(ll i=0, c1=1, c2=1; i<s.length(); ++i){
		h1[i+1] = (h1[i] + (s[i]*c1 % m)) % m;
		c1 = c1*p1 % m;
		h2[i+1] = (h2[i] + (s[i]*c2 % m)) % m;
		c2 = c2*p2 % m;
	}

	ll res = 0;

	int ct[27] = {};

	for(int sz=2; sz<s.length(); ++sz){
		++ct[sum(0, sz-1)];

		for(int rep=1; sz*rep<s.length(); ++rep){
			int bound = sum(sz*rep, s.length());
			for(int i=0; i<=bound; ++i) res += ct[i];
			if(!same(0, sz, sz*rep, sz*rep+sz)) break;
		}
	}

	std::cout << res << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
