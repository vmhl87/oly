#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

//:str
typedef struct segtree{
	vector<int> tree;
	vector<int> lazy;
	int n;
	void prop(int i){
		tree[i]=tree[i<<1]+tree[i<<1|1];
	}
	//:build
	void build(int i,int l,int r,vector<int> v){
		if(l==r){
			tree[i]=v[l-1];
			return;
		}
		int sp=(l+r)>>1;
		build(i<<1,l,sp,v);
		build(i<<1|1,sp+1,r,v);
		prop(i);
	}
	//:ctor
	segtree(vector<int> v):tree(v.size()*2),
	lazy(v.size()*2),n(v.size()){
		build(1,1,n,v);
	}
	//:spli
	void split(int i,int l,int r){
		lazy[i<<1]+=lazy[i];
		lazy[i<<1|1]+=lazy[i];
		// important: when an update gets split down,
		// it is removed from the "active lazy tree"
		// and propagated directly to node (this is
		// scuffed and may not work on double query)
		tree[i]+=lazy[i]*(r-l+1);
		lazy[i]=0;
	}
	//:upda
	// l,r are search range, ll,rr are node range
	void update(int i,int l,int r,int ll,int rr,int v){
		if(l==ll&&r==rr){
			lazy[i]+=v;
			return;
		}
		split(i,ll,rr);
		int sp=(ll+rr)>>1;
		if(l<=sp)update(i<<1,l,min(r,sp),ll,sp,v);
		if(r>sp)update(i<<1|1,max(l,sp+1),r,sp+1,rr,v);
	}
	void add(int l,int r,int v){
		update(1,l,r,1,n,v);
	}
	//:sum
	int trav(int i,int l,int r,int ll,int rr){
		if(l==ll&&r==rr)
			return tree[i]+lazy[i]*(r-l+1);
		int sp=(ll+rr)>>1,ret=0;
		split(i,ll,rr);
		if(l<=sp)ret+=trav(i<<1,l,min(r,sp),ll,sp);
		if(r>sp)ret+=trav(i<<1|1,max(l,sp+1),r,sp+1,rr);
		return ret;
	}
	int sum(int l,int r){
		return trav(1,l,r,1,n);
	}
}segtree;

//:main
int main(){
	int n;cin>>n;
	vector<int> v(n);
	for(int i=0;i<n;++i)
		cin>>v[i];
	segtree m(v);
	//:quer
	for(;;){
		int t;cin>>t;
		if(!t)break;
		if(t==1){
			for(int i=1;i<n+n;++i)
				cout<<i<<" +"<<m.lazy[i]<<' '
					<<m.tree[i]<<'\n';
		}
		if(t==2){
			int l,r,v;cin>>l>>r>>v;
			m.add(l,r,v);
		}
		if(t==3){
			int l,r;cin>>l>>r;
			cout<<m.sum(l,r)<<'\n';
		}
	}
}
//:end
