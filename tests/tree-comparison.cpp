#include <iostream>

template <typename T>
struct splaytree{
	struct node{
		node *c[2] = {}, *p = nullptr;
		T v;
	};

	node *root = nullptr;

	int side(node *N){
		if(N->p) return N->p->c[1] == N;
		return 0;
	}

	void move(node *N, node *M, int i){
		if(M->c[i]) M->c[i]->p = nullptr;
		if(N->p) N->p->c[side(N)] = nullptr;
		M->c[i] = N, N->p = M;
	}

	void rotate(node *N){
		int d = side(N);
		node *M = N->p;
		if(M->p) move(N, M->p, side(M));
		else root = N, M->c[d] = nullptr, N->p = nullptr;
		if(N->c[!d]) move(N->c[!d], M, d);
		move(M, N, !d);
	}

	void splay(node *N){
		while(N != root){
			node *M = N->p, *O = M->p;
			if(M == root) rotate(N);
			else if(side(N) == side(M)) rotate(M), rotate(N);
			else rotate(N), rotate(N);
		}
	}

	void erase(node *N){
		if(!N) return;

		splay(N);

		if(!N->c[0]) root = N->c[1];
		else if(!N->c[1]) root = N->c[0];
		else{
			root = N->c[0];
			node *p = root;
			while(p->c[1]) p = p->c[1];
			move(N->c[1], p, 1);
		}

		if(root) root->p = nullptr;
		delete N;
	}

	void insert(T v){
		node *N = new node;
		N->v = v;

		if(!root) root = N;
		else{
			node *p = root;

			while(p->c[p->v < v]) p = p->c[p->v < v];
			p->c[p->v < v] = N, N->p = p;

			splay(N);
		}
	}

	node* find(T v){
		if(root){
			node *p = root, *l = p;

			while(p){
				if(p->v == v){
					splay(p);
					return p;
				}
				l = p, p = p->c[p->v < v];
			}

			splay(l);
		}

		return nullptr;
	}

	void erase(T v) { erase(find(v)); }

	void toggle(T v){
		node *n = find(v);
		if(n) erase(n);
		else insert(v);
	}

	// -- debug --
	
	void print1(node *N){
		if(!N) return;
		print1(N->c[0]), std::cout << N->v << ' ', print1(N->c[1]);
	}

	void print2(node *N){
		if(!N) return;
#define V(x) ((x) ? (x)->v : 0 )
		std::cout << N->v << ": " << V(N->c[0]) << ' ' << V(N->c[1]) << '\n';
#undef V
		print2(N->c[0]);
		print2(N->c[1]);
	}

	void print(){
		std::cout << "[ ";
		print1(root);
		std::cout << "]\n";
		print2(root);
	}
};

#include <chrono>
#include <set>

const int maxn = 1e6;
int a[maxn];

int main(){
	splaytree<int> s1;
	std::set<int> s2;

	if(0) while(1){
		int v; std::cin >> v;
		s1.toggle(v), s1.print();
	}

	srand(time(NULL));
	for(int i=0; i<maxn; ++i) a[i] = rand()%maxn;

	{
		std::cout << "splay ";
		auto start = std::chrono::high_resolution_clock::now();
		for(int i=0; i<maxn; ++i) s1.toggle(a[i]);
		auto end = std::chrono::high_resolution_clock::now();
		std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << "ms\n";
	};

	{
		std::cout << "rbt   ";
		auto start = std::chrono::high_resolution_clock::now();
		for(int i=0; i<maxn; ++i) if(s2.count(a[i])) s2.erase(a[i]); else s2.insert(a[i]);
		auto end = std::chrono::high_resolution_clock::now();
		std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << "ms\n";
	};
}
