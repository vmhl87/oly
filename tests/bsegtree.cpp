#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef struct segtree{
	vector<int> tree;
	int n;
	segtree(vector<int> &v):tree(v.size()*2){
		n=v.size();
		for(int i=0;i<n;++i)tree[i+n]=v[i];
		for(int i=n-1;i>0;--i)
			tree[i]=max(tree[i<<1],tree[i<<1|1]);
	}
	// i is zero-indexed (ofc)
	void set(int i,int v){
		i+=n;tree[i]=v;i>>=1;
		while(i){
			tree[i]=max(tree[i<<1],tree[i<<1|1]);
			i>>=1;
		}
	}
	// [l,u) both zero-indexed
	int range(int l,int u){
		l+=n;u+=n;
		int ret=0;
		while(l<u){
			if(l&1)ret=max(ret,tree[l++]);
			if(u&1)ret=max(ret,tree[--u]);
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
