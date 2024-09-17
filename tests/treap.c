#include <stdlib.h>
#include <stdio.h>

struct node{
	int x, y;
	struct node *l, *r;
};

typedef struct node* pnode;

void split(pnode t, int x, pnode *l, pnode *r){
	if(!t) *l = *r = 0;
	else if(t->x <= x) split(t->r, x, &t->r, r), *l = t;
	else split(t->l, x, l, &t->l), *r = t;
}

void insert(pnode *t, pnode *i){
	if(!t[0]) *t = *i;
	else if(i[0]->y > t[0]->y) split(*t, i[0]->x, &i[0]->l, &i[0]->r), *t = *i;
	else insert(t[0]->x <= i[0]->x ? &t[0]->r : &t[0]->l, i);
}

void merge(pnode *t, pnode l, pnode r){
	if(!l || !r) *t = l ? l : r;
	else if(l->y > r->y) merge(&l->r, l->r, r), *t = l;
	else merge(&r->l, l, r->l), *t = r;
}

void erase(pnode *t, int x){
	if(!t[0]) return;
	else if(t[0]->x == x){
		pnode tmp = *t;
		merge(t, t[0]->l, t[0]->r);
		free(tmp);
	}else erase(x < t[0]->x ? &t[0]->l : &t[0]->r, x);
}

void print(pnode t){
	if(t->l) print(t->l);
	printf("%d ", t->x);
	if(t->r) print(t->r);
}

void add(pnode *t, int x){
	pnode next = malloc(sizeof(struct node));
	next->x = x, next->y = rand();
	insert(t, &next);
}

int main(){
	pnode treap = 0;
	for(int i=0; i<10; ++i) add(&treap, rand()%10);
	print(treap); printf("\n");
	erase(&treap, 3);
	print(treap); printf("\n");
}
