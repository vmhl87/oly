#include <iostream>

struct node{
	int c, s, l, r;
};

node a[600000];

int b[600000];

void remove(int i){
	a[a[i].l].r = a[i].r;
	a[a[i].r].l = a[i].l;
}

int root[6000000];

int find(int i){
	if(root[i] == i) return i;
	return root[i] = find(root[i]);
}

void merge(int a, int b){
	a = find(a), b = find(b);
	if(a == b) return;

	root[a] = b;
}

int main(){
	int n, q; std::cin >> n >> q;

	for(int i=1; i<=n; ++i){
		b[i] = 1;
		a[i] = {i, 1, i-1, i+1};
		root[i] = i;
	}

	a[0].r = 1;
	a[n+1].l = n;

	while(q--){
		int t; std::cin >> t;

		if(t&1){
			int x, c; std::cin >> x >> c;

			x = find(x);

			b[a[x].c] -= a[x].s;
			b[c] += a[x].s;
			a[x].c = c;

			if(a[x].c == a[a[x].l].c){
				a[x].s += a[a[x].l].s;
				merge(a[x].l, x);
				remove(a[x].l);
			}

			if(a[x].c == a[a[x].r].c){
				a[x].s += a[a[x].r].s;
				merge(a[x].r, x);
				remove(a[x].r);
			}
		}else{
			int c; std::cin >> c;
			std::cout << b[c] << '\n';
		}
	}
}
