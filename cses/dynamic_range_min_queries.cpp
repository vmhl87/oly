#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef struct segtree{
	vector<int> tree;
	int n;
	void prop(int i){
		tree[i]=min(tree[i<<1],tree[i<<1|1]);
	}
	segtree(int len):tree(len*2),n(len){
		for(int i=0;i<len;++i)
			cin>>tree[i+len];
		for(int i=len-1;i>0;--i)prop(i);
	}
	void set(int i,int v){
		i+=n;tree[i]=v;i>>=1;
		while(i){
			prop(i);
			i>>=1;
		}
	}
	int cr(int a,int b){
		if(a<0)return b;
		return min(a,b);
	}
	int range(int l,int r){
		l+=n;r+=n-1;
		int ret=-1;
		while(l<=r){
			if(l&1)ret=cr(ret,tree[l++]);
			if(~r&1)ret=cr(ret,tree[r--]);
			l>>=1;r>>=1;
		}
		return ret;
	}
}segtree;

int main(){
	int n,q;cin>>n>>q;
	segtree m(n);
	for(int i=0;i<q;++i){
		int t,a,b;cin>>t>>a>>b;
		if(t&1)m.set(a-1,b);
		else cout<<m.range(a-1,b)<<'\n';
	}
}
