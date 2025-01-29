#include <iostream>
#include <array>

using ll = long long;
const int N = 3e5;

int a[N][3];

int sqr(ll a, ll b){
	ll r = a*a + b*b;
	ll res = 0;
	for(ll x=1<<21; x; x/=2)
		if((res+x)*(res+x) <= r)
			res += x;
	return (int) res;
}

int X, Y;

int cm(int a, int b){
	return std::abs(X-a) + std::abs(Y-b) + sqr(a, b);
}

int calc(std::array<int, 4> v){
	return cm(
			std::max(v[2], std::min(v[0], X)),
			std::max(v[3], std::min(v[1], Y))
		);
}

struct node{
	std::array<int, 4> b;
	node *l, *r, *p;
	bool del, lc;
	int res;
};

node *root = new node;

void dfs(node *i){
	if(i->l != 0){
		dfs(i->l), dfs(i->r);
	}else{
		for(int j=0; j<4; ++j)
			std::cout << i->b[j] << " \n"[j==3];
	}
}

void fix(node *i){
	//while(i){
		i->b[0] = i->l->b[0];
		i->b[1] = i->l->b[1];
		i->b[2] = i->r->b[2];
		i->b[3] = i->r->b[3];
		i->res = std::min(i->l->res, i->r->res);
		//i = i->p;
	//}
}

void add(int x, int y, node *i){
	if(i->del) return;
	const auto &[a, b, c, d] = i->b;
	if(i->l){
		if((a < x && b < y) || (c > x && d > y)) return;
		else if((x > a && y < d) || (x < c && y > b)){
			node *par = i->p, *next = i->lc ? par->r : par->l;
			if(root != par){
				node *rp = par->p;
				next->lc = par->lc;
				if(par->lc) rp->l = next;
				else rp->r = next;
				next->p = rp;
				delete par;
				delete i;
			}else{
				delete root;
				delete i;
				root = next;
				next->p = 0;
			}
		}else{
			add(x, y, i->l);
			add(x, y, i->r);
		}
		fix(i);
	}else{
		if(x < a && x > c && y < b && y > d){
			i->l = new node; i->l->l = 0; i->l->lc = 1;
			i->r = new node; i->r->l = 0; i->r->lc = 0;
			i->l->p = i;
			i->r->p = i;
			i->l->b = {a, b, x, y};
			i->r->b = {x, y, c, d};
			i->l->res = calc(i->l->b);
			i->r->res = calc(i->r->b);
		}else if(x < a && y < b){
			i->b = {a, b, std::max(c, x), std::max(d, y)};
			i->res = calc(i->b);
			//if(i->p) fix(i->p);
		}else if(x > c && y > d){
			i->b = {std::min(a, x), std::min(b, y), c, d};
			i->res = calc(i->b);
			//if(i->p) fix(i->p);
		}else{
			node *par = i->p, *next = i->lc ? par->r : par->l;
			if(root != par){
				node *rp = par->p;
				next->lc = par->lc;
				if(par->lc) rp->l = next;
				else rp->r = next;
				next->p = rp;
				delete par;
				delete i;
				//fix(rp);
			}else{
				delete root;
				delete i;
				root = next;
				next->p = 0;
			}
		}
	}
}

int main(){
	int n, t; std::cin >> n >> t;
	std::cin >> X >> Y;

	for(int i=0; i<n; ++i)
		for(int j=0; j<3; ++j)
			std::cin >> a[i][j];
	
	root->b = {(int)2e6, (int)2e6, 0, 0};
	root->res = sqr(X, Y);

	for(int i=0, p=0; i<t; ++i){
		while(p < n && a[p][0] <= i)
			add(a[p][1], a[p][2], root), ++p;
		//std::cout << "---\n";
		//dfs(root);
		//std::cout << "---\n";
		std::cout << root->res << '\n';
	}
}
