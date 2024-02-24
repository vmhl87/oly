#include <iostream>
#include <vector>
using namespace std;

#define mx(a,b) (a)>(b)?(a):(b)
#define mn(a,b) (a)<(b)?(a):(b)

typedef struct segtree{
	vector<int> tree;
	int n;
	segtree(vector<int> &v):tree(v.size()*2){
		n=v.size();
		for(int i=0;i<n;++i)tree[i+n]=v[i];
		for(int i=n-1;i>0;--i)
			tree[i]=mx(tree[i<<1],tree[(i<<1)+1]);
	}
	void set(int i,int v){
		i+=n;tree[i]=v;i>>=1;
		while(i){
			tree[i]=mx(tree[i<<1],tree[(i<<1)+1]);
			i>>=1;
		}
	}
	int range(int l,int u){
		l+=n;u+=n-1;
		int ret=0;
		while(l<=u){
			if(l&1){
				ret=mx(ret,tree[l]);
				l++;
			}
			if(~u&1){
				ret=mx(ret,tree[u]);
				u--;
			}
			l>>=1;u>>=1;
		}
		return ret;
	}
}segtree;

int main(){
	int n;cin>>n;
	vector<int> v(n);
	for(int i=0;i<n;i++)cin>>v[i];
	segtree m(v);
	for(;;){
		int t,a,b;cin>>t;
		if(!t)break;
		cin>>a>>b;
		if(t&1)m.set(a,b);
		else cout<<m.range(a,b)<<'\n';
	}
}
