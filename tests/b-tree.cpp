#include <iostream>

template <typename T, int K>
struct btree{
	struct node{
		node *c[K+2];
		T k[K+1];
		int z;
	};

	node *root = new node;
	int h = 1;

	int count(T v){
		node *p = root;
		
		for(int i=0; p && i<p->z; ++i){
			if(p->k[i] == v) return 1;
			if(p->k[i] > v) p = p->c[i], i = -1;
			else if(i == p->z-1) p = p->c[i+1], i = -1;
		}

		return 0;
	}

	void add(node *p, T v, node *w){
		for(int i=0; i<p->z; ++i){
			if(p->k[i] > v){
				T a = p->k[i];
				p->k[i] = v;
				v = a;

				node *b = p->c[i+1];
				p->c[i+1] = w;
				w = b;
			}
		}

		p->c[p->z+1] = w;
		p->k[p->z] = v;
		++p->z;
	}

	node* split(node *p){
		node *n = new node;
		int j = 1+K/2;

		for(int k=j; k<p->z; ++k){
			n->k[k-j] = p->k[k];
			n->c[k-j] = p->c[k];
			++n->z;
		}

		n->c[K-j] = p->c[K];
		p->z = j-1;

		return n;
	}

	void insert(node *p, int d, T v){
		if(d == h-1) add(p, v, nullptr);
		else{
			for(int i=0; i<p->z; ++i){
				if(p->k[i] == v) return;
				if(p->k[i] > v) 0;
				else if(i == p->z-1) ++i;
				else continue;

				insert(p->c[i], d+1, v);

				if(p->c[i]->z > K) add(p, p->c[i]->k[K/2], split(p->c[i]));

				break;
			}
		}
	}

	void insert(T v){
		insert(root, 0, v);

		if(root->z > K){
			node *n = root, *m = split(root);

			root = new node;
			root->z = 1, ++h;

			root->c[0] = n;
			root->c[1] = m;
			root->k[0] = n->k[K/2];
		}
	}

	void erase(node *p, int d, T v){
		for(int i=0; i<p->z; ++i){
			if(p->k[i] == v){
				for(i; i<p->z; ++i){
					p->k[i] = p->k[i+1];
					p->c[i+1] = p->c[i+2];
				}

				--p->z;
				return;
			}

			if(p->k[i] > v) 0;
			else if(i == p->z-1) ++i;
			else continue;

			if(d < h) erase(p->c[i], d+1, v);

			break;
		}
	}

	void erase(T v){
		erase(root, 1, v);
	}

	// -- debug --

	void print1(node *p){
		if(!p) return;

		print1(p->c[0]);
		
		for(int i=0; i<p->z; ++i){
			std::cout << p->k[i] << ' ';
			print1(p->c[i+1]);
		}
	}

	void print2(node *p, int d){
		if(!p) return;

		for(int i=0; i<p->z; ++i)
			std::cout << p->k[i] << " :"[i==p->z-1&&d<h];

		if(d<h) for(int i=0; i<=p->z; ++i)
			std::cout << ' ' << p->c[i]->k[0];

		std::cout << '\n';

		if(d<h) for(int i=0; i<=p->z; ++i)
			print2(p->c[i], d+1);
	}

	void print(){
		std::cout << "[ ";
		print1(root);
		std::cout << "]\n";
		print2(root, 1);
	}
};

int main(){
	btree<int, 5> t;

	while(1){
		int v; std::cin >> v;
		if(t.count(v)) t.erase(v);
		else t.insert(v);

		t.print();
	}
}
