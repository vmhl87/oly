// oh le blackbox

namespace lct{
	const int N=100050;
	int go[N][2],fa[N];
	int pd(int x){ return go[fa[x]][0]==x?0:go[fa[x]][1]==x?1:-1;}
	void rot(int x)
	{
		int y=fa[x],z=fa[y],p=pd(x),q=pd(y),w=go[x][p^1];
		if(q!=-1) go[z][q]=x;go[x][p^1]=y;go[y][p]=w;
		if(w) fa[w]=y;fa[x]=z;fa[y]=x;
	}
	void splay(int x){ while(pd(x)!=-1){ if(pd(fa[x])!=-1) rot(pd(fa[x])==pd(x)?fa[x]:x);rot(x);}}
	void access(int x){ for(splay(x),go[x][1]=0;fa[x];rot(x)) splay(fa[x]),go[fa[x]][1]=x;}
	int rt(int x){ access(x);while(go[x][0]) x=go[x][0];splay(x);return x;}
	bool same(int u,int v){ return rt(u)==rt(v);}
	void link(int u,int v){ if(rt(u)==rt(v))return;splay(u);fa[u]=v;}
	void cut(int u,int v)
	{
		if(rt(u)!=rt(v))return;splay(u);access(v);
		fa[v]=fa[v]==u?0:fa[v];fa[u]=fa[u]==v?0:fa[u];
	}
}

// oh this only works on trees rip

#include <iostream>

int main(){
	lct::link(1, 2);
	lct::link(3, 4);
	lct::link(2, 3);
	
	std::cout << lct::same(1, 4) << '\n';
	std::cout << lct::same(1, 5) << '\n';

	lct::cut(2, 3);
	std::cout << lct::same(1, 4) << '\n';

	lct::link(4, 5);
	std::cout << lct::same(3, 5) << '\n';
}
