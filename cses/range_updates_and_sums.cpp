#include <iostream>
#include <vector>
using namespace std;

typedef struct segtree{
	struct op{
		int a=0,m=0;
	};
	vector<int> tree;
	vector<int> lazy;
	int n;
	void prop(int i){
		tree[i]=tree[i<<1]+tree[i<<1|1];
	}
	segtree(int l):tree(l*2),lazy(l*2),n(l){
		for(int i=0;i<l;++i)cin>>tree[i+l];
		for(int i=l-1;i>0;--i)prop(i);
	}
	void comb(int i,int j){
		lazy[i].a*=lazy[j].m;
		lazy[i].m*=lazy[j].m;
		lazy[i].a+=lazy[j].a;
	}
	void push(int i){
		if(i<n){
			comb(i<<1,i);
			comb(i<<1|1,i);
		}else{
			tree[i]*=lazy[i].m;
			tree[i]+=lazy[i].a;
		}
		lazy[i].a=0;lazy[i].m=1;
	}
	void set(int l,int r,int v){
		l+=n;r+=n-1;
		while(l<=r){
			if(l&1){
				lazy[l].a=v;
				lazy[l].m=0;
				l++;
			}
			if(~r&1){
				lazy[r].a=v;
				lazy[r].m=0;
				r--;
			}
			l>>=1;r>>=1;
		}
	}
}segtree;

int main(){
	int n,q;cin>>n>>q;
	segtree m(n);
	while(q--){
		int t;cin>>t;
		if(t==3){
			int a,b;cin>>a>>b;
			cout<<m.sum(a-1,b)<<'\n';
		}else if(t==2){
			int a,b,x;cin>>a>>b>>x;
			m.set(a-1,b,x);
		}else{
			int a,b,x;cin>>a>>b>>x;
			m.add(a-1,b,x);
		}
	}
}
