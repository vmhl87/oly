#include <iostream>
#include <vector>
#include <cmath>

template <typename T>
struct sqrt_tree{
	T *pf, *sf, *bt;
	sqrt_tree *c;
	int sz;

	T op(T a, T b){
		return std::min(a, b);
	}

	void build(std::vector<T> &v, int l, int r){
		int n = r-l;

		if(n > 4){
			sz = std::ceil(std::sqrt(n));

			pf = new T[sz*sz];
			sf = new T[sz*sz];
			bt = new T[sz*sz];
			c = new sqrt_tree<T>[sz];

			{
				T z = v[l];
				for(int i=0; i<n; ++i){
					pf[i] = z;
					if(i == n-1) break;
					if((i+1) % sz == 0) z = v[i+1+l];
					else z = op(z, v[i+l+1]);
				}
			};

			{
				T z = v[r-1];
				for(int i=n-1; i>=0; --i){
					sf[i] = z;
					if(!i) break;
					if(i % sz == 0) z = v[i-1+l];
					else z = op(z, v[i+l-1]);
				}
			};

			for(int i=0; i<sz; ++i){
				T z = sf[i*sz];
				for(int j=1; j<sz; ++j){
					bt[i*sz+j] = z;
					z = op(z, sf[j*sz]);
				}
			}

			for(int i=0; i<sz; ++i) c[i].build(v, l+sz*i, std::min(l+sz*(i+1), r));

		}else{
			sz = -1;
			pf = new T[n];
			for(int i=l; i<r; ++i) pf[i-l] = v[i];
		}
	}

	sqrt_tree(){}

	sqrt_tree(std::vector<T> &v){
		build(v, 0, v.size());
	}

	T query(int l, int r){
		if(sz == -1){
			T res = pf[l];
			for(int i=l+1; i<r; ++i) res = op(res, pf[i]);
			return res;

		}else{
			if(l/sz == (r-1)/sz) return c[l/sz].query(l-sz*(l/sz), r-sz*(l/sz));
			else if(l/sz + 1 == (r-1)/sz) return op(sf[l], pf[r-1]);
			return op(op(sf[l], bt[sz*(1+l/sz)+(r-1)/sz]), pf[r-1]);
		}
	}
};

int main(){
	int n, q; std::cin >> n >> q;

	std::vector<int> v(n);
	for(int i=0; i<n; ++i) std::cin >> v[i];
	sqrt_tree<int> t(v);

	while(q--){
		int l, r; std::cin >> l >> r, --l;
		std::cout << t.query(l, r) << '\n';
	}
}
