#include <iostream>
#include <vector>
using namespace std;

typedef struct segtree{
	vector<long long> tree;
	vector<long long> lazy;
	int n;
	void prop(long long i){
		tree[i]=tree[i<<1]+tree[i<<1|1];
	}
	segtree(vector<long long> v):tree(v.size()*2),lazy(v.size()*2),n(v.size()){
		for(int i=0;i<n;++i)tree[i+n]=v[i];
		for(int i=n-1;i>0;--i)prop(i);
	}
	void set(int i,long long v){
		i+=n;tree[i]+=v;i>>=1;
		while(i){
			prop(i);
			i>>=1;
		}
	}
	void rangeup(int l,int r,long long v){
		l+=n;r+=n-1;
		while(l<=r){
			if(l&1)lazy[l++]+=v;
			if(~r&1)lazy[r--]+=v;
			l>>=1;r>>=1;
		}
	}
	void push(int i){
		if(!i||i>=n)return;
		lazy[i<<1]+=lazy[i];
		lazy[i<<1|1]+=lazy[i];
		lazy[i]=0;
	}
	long long get(int i){
		i+=n;int node=0,p=31;
		while(node<n){
			node=i>>p;
			p--;
			push(node);
		}
		return tree[i]+lazy[i];
	}
}segtree;

int main(){
	int n,q;cin>>n>>q;
	vector<long long> v(n);
	for(int i=0;i<n;++i)
		cin>>v[i];
	segtree m(v);
	while(q--){
		int t;cin>>t;
		if(t&1){
			int a,b;long long u;
			cin>>a>>b>>u;
			m.rangeup(a-1,b,u);
		}else{
			long long k;cin>>k;
			cout<<m.get(k-1)<<'\n';
		}
	}
}
