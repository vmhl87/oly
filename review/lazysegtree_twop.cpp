#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef struct segtree{
	vector<int> tree;
	struct op{
		int add=0;
		int mult=1;
	};
	vector<op> lazy;
	int n;
	void prop(int i){
		tree[i]=tree[i<<1]+tree[i<<1|1];
	}
	// built recursively to preserve order
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
	segtree(int len):tree(len*2),lazy(len*2),n(len){
		vector<int> v(len);
		for(int i=0;i<len;++i)cin>>v[i];
		build(1,1,len,v);
	}
	void push(int i,op o){
		lazy[i].add=lazy[i].add*o.mult+o.add;
		lazy[i].mult*=o.mult;
	}
	void split(int i){
		push(i<<1,lazy[i]);
		push(i<<1|1,lazy[i]);
		lazy[i].add=0;lazy[i].mult=1;
	}
	// shouldn't be done recursively but wtv
	// expects 1-indexing and bounding (i.e. 3,5 covers
	// all nodes 3,4,5)
	void update(int i,int l,int r,int ll,int rr,op o){
		if(l==ll&&r==rr){
			push(i,o);
			return;
		}
		split(i);
		int sp=(ll+rr)>>1;
		if(l<=sp)update(i<<1,l,min(sp,r),ll,sp,o);
		if(r>=sp+1)update(i<<1|1,max(sp+1,l),r,sp+1,rr,o);
	}
	void setrange(int l,int r,int v){
		op o;o.add=v;o.mult=0;
		update(1,l,r,1,n,o);
	}
	void addrange(int l,int r,int v){
		op o;o.add=v;
		update(1,l,r,1,n,o);
	}
	// very similar to recursive update
	int range(int i,int l,int r,int ll,int rr){
		// cout<<i<<','<<l<<','<<r<<','<<ll<<','<<rr<<' '<<tree[i]<<'\n';
		if(l==ll&&r==rr){
			return tree[i]*lazy[i].mult+lazy[i].add*(rr-ll+1);
		}
		split(i);
		int sp=(ll+rr)>>1,ret=0;
		if(l<=sp)ret+=range(i<<1,l,min(r,sp),ll,sp);
		if(r>=sp+1)ret+=range(i<<1|1,max(l,sp+1),r,sp+1,rr);
		return ret;
	}
	int sum(int l,int r){
		return range(1,l,r,1,n);
	}
}segtree;

int main(){
	int n;cin>>n;
	segtree m(n);
	for(;;){
		int t;cin>>t;
		if(!t)break;
		if(t==1){
			for(int i=1;i<n*2;++i)
				cout<<m.tree[i]<<" +"<<m.lazy[i].add<<" *"<<m.lazy[i].mult<<'\n';
		}
		if(t==2){
			int a,b,v;cin>>a>>b>>v;
			m.setrange(a,b,v);
		}
		if(t==3){
			int a,b,v;cin>>a>>b>>v;
			m.addrange(a,b,v);
		}
		if(t==4){
			int a,b;cin>>a>>b;
			cout<<m.sum(a,b)<<'\n';
		}
	}
}
