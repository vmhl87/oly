#include <iostream>

struct node{
	node *l, *r;
	int id, sz;
	bool flip;
};

node root;

void build(node *x, int n, int i){
	x->sz = n, x->id = i;
	if(n > 1){
		x->l = new node;
		x->r = new node;
		build(x->l, n/2, i);
		build(x->r, n-(n/2), i+(n/2));
	}
}

void push(node *x){
	if(x->flip && x->sz > 1){
		std::swap(x->l, x->r);
		x->l->flip ^= 1;
		x->r->flip ^= 1;
		x->flip = 0;
	}
}

int at(int i, node *x = &root){
	push(x);

	if(x->sz == 1) return x->id;
	if(i >= x->l->sz) return at(i-x->l->sz, x->r);
	return at(i, x->l);
}

void traverse(int n){
	for(int i=0; i<n; ++i)
		std::cout << at(i) << " \n"[i==n-1];
}

int main(){
	int n; std::cin >> n;
	build(&root, n, 1);

	traverse(n);

	root.r->flip = 1;

	traverse(n);
}
