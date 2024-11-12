// zeocool orz

namespace splaty{
	struct Node{
		int val;
		ar<Node*, 2> g;
		Node *par;
		
		bool side(){
			return par->g[1] == this;
		}
		
		void attach(bool i, Node *n){
			if(n)n->par = this;
			g[i] = n;
		}
		
		void rotate(){
			auto p = par;
			bool i = side();
			if(p->par)p->par->attach(p->side(), this);
			else par = nullptr;
			p->attach(i, g[!i]);
			attach(!i, p);
		}
		
		void splay(){
			while(par){
				if(par->par){
					if(side() == par->side())par->rotate();
					else rotate();
				}
				
				rotate();
			}
		}
		
		array<Node*, 2> split(){
			splay();
			auto r = g[1];
			if(r)r->par = nullptr;
			g[1] = nullptr;
			return {this, r};
		}
	};
	
	Node *root;
	
	void insert(Node *x){
		if(!root){
			root = x;
			return;
		}
		auto y = root;
		while(1){
			auto &n = y->g[x->val > y->val];
			if(!n){
				n = x;
				n->par = y;
				root = n;
				n->splay();
				return;
			}
			y = n;
		}
		return;
	}
	
	Node *go(Node *x, bool i){
		while(x->g[i])x = x->g[i];
		return x;
	}
	
	Node *join(Node *a, Node* b){
		if(!a){
			b->par = nullptr;
			return b;
		}
		Node *mx = go(a, 1);
		mx->splay();
		mx->g[1] = b;
		mx->par = nullptr;
		return mx;
	}
	
	void erase(Node *x){
		x->splay();
		root = join(x->g[0], x->g[1]);
	}
	Node *find(int a){
		auto x = root;
		while(x && a != x->val){
			auto n = x->g[a > x.val];
			if(!n)x->splay;
			x = n;
		}
		return x;
	}
	
};
