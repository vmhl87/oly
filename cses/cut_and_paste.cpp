// I used an order-statistic skiplist because I don't know treap
// not much to say here from an algorithmic standpoint; this is
// kinda a textbook skiplist operation (implemented weirdly)

#include <algorithm>
#include <iostream>
#include <array>
#include <cmath>

const int maxn = 2e5, lvl = 11;

struct node{
	char v = '$';           // head and tail delineator
	node *f[lvl], *b[lvl];  // next nodes
	int fl[lvl], bl[lvl];   // length to next node
	int h = lvl-1;
};

node s[maxn+2];

node *find(int i){
	node *res = s;  // me when arrays are pointers

	for(int j=lvl-1; i; --j){
		while(res->fl[j] <= i)
			i -= res->fl[j], res = res->f[j];
	}

	return res;
}

std::array<int, 2> ord[maxn];  // randomize initial order bc yes

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);
	srand(69);  // this is important (trust)

	int n, m; std::cin >> n >> m;

	for(int i=0; i<n; ++i)
		std::cin >> s[i+1].v;

	{
		int p = 0, v = 1;
		float f = powf(n, 1.0/lvl);

		for(float s=n/f; s && v<lvl; s/=f, ++v){
			for(int i=0; i<s; ++i, ++p)
				ord[p][1] = v;
		}

		for(int i=0; i<n; ++i) ord[i][0] = rand();

		std::sort(ord, ord+n);

		for(int i=0; i<n; ++i) s[i+1].h = ord[i][1];
	}

	// build interconnects

	node *p[lvl];
	for(int i=0; i<lvl; ++i) p[i] = s;

	for(int i=1; i<=n+1; ++i){
		for(int j=0; j<=s[i].h; ++j){
			p[j]->f[j] = s+i;
			p[j]->fl[j] = s+i-p[j];
			s[i].b[j] = p[j];
			s[i].bl[j] = s+i-p[j];
			p[j] = s+i;
		}
	}

	// queries

	while(m--){
		int a, b; std::cin >> a >> b;

		// find ending nodes of the desired segment
		// then determine all of the edges that need to be cut

		node *start = find(a), *end = find(b);

		node *left[lvl], *right[lvl];
		int lp[lvl], rp[lvl], lf = 0, rf = 0;

		// find outward side of edges & index them

		int lpp = a-(start->bl[0]);

		for(node *p=start->b[0]; lf<lvl;){
			for(; lf<=p->h; ++lf)
				left[lf] = p, lp[lf] = lpp;
			lpp -= p->bl[p->h];
			p = p->b[p->h];
		}

		int rpp = b+(end->fl[0]);

		for(node *p=end->f[0]; rf<lvl;){
			for(; rf<=p->h; ++rf)
				right[rf] = p, rp[rf] = rpp;
			rpp += p->fl[p->h];
			p = p->f[p->h];
		}

		// find inward side of edges

		node *leftright[lvl], *rightleft[lvl];
		int lrp[lvl], rlp[lvl];

		for(int i=0; i<lvl; ++i){
			leftright[i] = left[i]->f[i];
			lrp[i] = lp[i]+left[i]->fl[i];
			rightleft[i] = right[i]->b[i];
			rlp[i] = rp[i]-right[i]->bl[i];
		}

		// re-arrange edges

		for(int i=0; i<lvl; ++i){
			if(left[i]->f[i] == right[i]){
				left[i]->fl[i] -= (b-a+1);
				right[i]->bl[i] -= (b-a+1);

				node *x = s[n+1].b[i];

				s[n+1].bl[i] += (b-a+1);
				x->fl[i] += (b-a+1);

			}else{
				left[i]->f[i] = right[i];
				right[i]->b[i] = left[i];

				left[i]->fl[i] = rp[i]-lp[i]-(b-a+1);
				right[i]->bl[i] = rp[i]-lp[i]-(b-a+1);

				node *x = s[n+1].b[i];

				x->f[i] = leftright[i];
				leftright[i]->b[i] = x;
				int ll = x->fl[i] + lrp[i]-a;
				x->fl[i] = ll;
				leftright[i]->bl[i] = ll;

				s[n+1].b[i] = rightleft[i];
				rightleft[i]->f[i] = s+n+1;
				int rl = b-rlp[i] + 1;
				s[n+1].bl[i] = rl;
				rightleft[i]->fl[i] = rl;
			}
		}
	}

	// profit

	for(node *i=s[0].f[0]; i->v != '$'; i=i->f[0])
		std::cout << i->v;
	std::cout << '\n';
}
