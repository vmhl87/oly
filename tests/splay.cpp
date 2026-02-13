#include <iostream>

template <typename T>
struct splaytree{
	struct node{
		node *c[2] = {}, *p = nullptr;
		T v;
	};

	node *root = nullptr;

	int side(node *a){
		return a->p->c[1] == a;
	}

	void move(node *a, node *b, int s){
		if(b->c[s]) b->c[s]->p = nullptr;
		if(a->p) a->p->c[side(a)] = nullptr;
		b->c[s] = a, a->p = b;
	}

	void rotate(node *a){
		node *b = a->p;
		int d = side(a);
		a->p = nullptr, b->c[d] = nullptr;
		if(b->p) move(a, b->p, side(b));
		if(a->c[!d]) move(a->c[!d], b, d);
		if(root == b) root = a;
		move(b, a, !d);
	}

	void splay(node *a){
		while(a->p){
			node *b = a->p, *c = b->p;
			if(!c) rotate(a);
			else if(side(a) == side(b))
				rotate(b), rotate(a);
			else rotate(a), rotate(a);
		}
	}

	node* find(T v){
		if(!root) return nullptr;

		node *p = root, *l = p;

		while(p){
			if(p->v == v) l = p, p = nullptr;
			else l = p, p = p->c[p->v < v];
		}

		splay(l);

		return l->v == v ? l : nullptr;
	}

	void insert(T v){
		node *a = new node;
		a->v = v;

		if(!root) root = a;
		else{
			node *p = root;

			while(p->c[p->v < v]) p = p->c[p->v < v];
			p->c[p->v < v] = a, a->p = p;

			splay(a);
		}
	}

	void erase(node *a){
		splay(a);

		if(!a->c[0]) root = a->c[1];
		else if(!a->c[1]) root = a->c[0];
		else{
			node *p = (root = a->c[0]);
			while(p->c[1]) p = p->c[1];
			move(a->c[1], p, 1);
		}

		if(root) root->p = nullptr;

		delete a;
	}

	void erase(T v){
		node *a = find(v);
		if(a) erase(a);
	}

	// -- debug/prettyprint --
	
	void print1(node *a){
		if(!a) return;

		print1(a->c[0]);
		std::cout << a->v << ' ';
		print1(a->c[1]);
	}

	void print2(node *a){
		if(!a) return;
		
#define d(i) (a->c[i] ? a->c[i]->v : 0)
		std::cout << a->v << ": " << d(0) << ' ' << d(1) << '\n';
#undef d

		print2(a->c[0]), print2(a->c[1]);
	}

	void print(){
		std::cout << "[ ";
		print1(root);
		std::cout << "]\n";
		print2(root);
	}
};

int main(){
	splaytree<int> t;

	while(1){
		int x; std::cin >> x;
		if(t.find(x)) t.erase(x);
		else t.insert(x);

		t.print();
	}
}
