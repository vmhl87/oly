#include <iostream>

using ll = long long;
const int M = 998244353,
          N = 2e5;

//\\// modfrac
	struct f{
		ll a, b;

		ll o(){
			ll r = a;
			for(ll p=M-2; p; p/=2, b=b*b%M)
				if(p&1) r = r*b % M;
			return r;
		}
	};

	f mul(f a, f b){
		return {
			a.a*b.a % M,
			a.b*b.b % M,
		};
	}

	f add(f a, f b){
		return {
			(a.a*b.b + b.a*a.b) % M,
			a.b*b.b % M,
		};
	}

f a[N], t[N*4], z[N*4];
bool Z[N*4];

//\\// segtree
	void b(int i, int l, int r){
		if(l == r) t[i] = a[l];
		else{
			int m = (l+r)/2;
			b(i*2, l, m), b(i*2+1, m+1, r);
			t[i] = add(t[i*2], t[i*2+1]);
		}
	}

	void p(int i, int l, int r){
		if(!Z[i]) return;
		Z[i] = 0;
		if(l != r){
			int m = (l+r)/2;
			Z[i*2] = 1, z[i*2] = z[i], t[i*2] = mul(z[i], {m-l+1, 1});
			Z[i*2+1] = 1, z[i*2+1] = z[i], t[i*2+1] = mul(z[i], {r-m, 1});
		}
	}

	f q(int i, int l, int r, int ll, int rr){
		if(r < ll || l > rr) return {0, 1};
		else if(l >= ll && r <= rr) return t[i];
		else{
			p(i, l, r);
			int m = (l+r)/2;
			return add(q(i*2, l, m, ll, rr), q(i*2+1, m+1, r, ll, rr));
		}
	}

	void s(int i, int l, int r, int ll, int rr, f x){
		if(r < ll || l > rr) return;
		else if(l >= ll && r <= rr) Z[i] = 1, z[i] = x, t[i] = mul(x, {r-l+1, 1});
		else{
			Z[i] = 0;
			int m = (l+r)/2;
			s(i*2, l, m, ll, rr, x);
			s(i*2+1, m+1, r, ll, rr, x);
			t[i] = add(t[i*2], t[i*2+1]);
		}
	}

int main(){
	int n, m; std::cin >> n >> m;
	for(int i=0; i<n; ++i) std::cin >> a[i].a, a[i].b = 1;

	b(1, 0, n-1);

	for(int i=0; i<m; ++i){
		int l, r; std::cin >> l >> r;
		f x = mul(q(1, 0, n-1, --l, --r), {1, r-l+1});
		s(1, 0, n-1, l, r, x);
	}

	for(int i=0; i<n; ++i) std::cout << q(1, 0, n-1, i, i).o() << " \n"[i==n-1];
}
