#include <iostream>
#include <string>

struct node{
	char c;
	int pfx;
	node *l, *r;
};

node n[(int)1e6 + 10];

int main(){
	//freopen("censor.in", "r", stdin);
	//freopen("censor.out", "w", stdout);

	std::string s, t; std::cin >> s >> t;
	s = "S" + s + "E";

	int m = s.length();

	for(int i=0; i<m; ++i)
		n[i].c = s[i];

	for(int i=0; i<m-1; ++i)
		n[i].r = n+i+1;

	for(int i=1; i<m; ++i)
		n[i].l = n+i-1;

	node *p = n+1;

	while(p->c != 'E'){
		int np = p->l->pfx + 1;
		if(np > s.length() || t[np-1] != p->c)
			np = t[0] == p->c;

		p->pfx = np;

		if(np == t.length())
			for(int i=0; i<t.length(); ++i){
				p->l->r = p->r;
				p->r->l = p->l;
				p = p->l;
			}

		p = p->r;
	}

	p = n->r;

	while(p->c != 'E')
		std::cout << p->c, p = p->r;

	std::cout << '\n';
}
