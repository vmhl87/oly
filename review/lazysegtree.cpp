#include <iostream>
#include <vector>
using namespace std;

typedef struct segtree{
	vector<int> tree;
	vector<int> lazy;
	int n;
	void prop(int i){
		tree[i]=tree[i<<1]+tree[i<<1|1];
	}
	segtree(vector<int> v):tree(v.size()*2),lazy(v.size()*2),n(v.size()){
		for(int i=0;i<n;++i)tree[i+n]=v[i];
		for(int i=n-1;i>0;--i)prop(i);
	}
	void set(int i,int v){
		i+=n;tree[i]+=v;i>>=1;
		while(i){
			prop(i);
			i>>=1;
		}
	}
	void rangeup(int l,int r,int v){
		l+=n;r+=n-1;
		while(l<=r){
			if(l&1)lazy[l++]+=v;
			if(~r&1)lazy[r--]+=v;
			l>>=1;r>>=1;
		}
	}
	void push(int i){
		if(i>=n)return;
		lazy[i<<1]+=lazy[i];
		lazy[i<<1|1]+=lazy[i];
		lazy[i]=0;
	}
	int get(int i){
		i+=n;int node=0,p=1<<31;
		while(node<i){
			node<<=1;
			if(i&p)node++;
			p>>=1;
			push(node);
		}
		return tree[i]+lazy[i];
	}
}segtree;

string f(int i){
	string ret;
	if(i>9)ret+=('0'+i/10);
	else ret+=' ';
	ret+=('0'+i%10);
	return ret;
}

int main(){
	int n;cin>>n;
	vector<int> v(n);
	for(int i=0;i<n;++i)
		cin>>v[i];
	segtree m(v);
	for(;;){
		int t;cin>>t;
		if(t==1){
			int a;cin>>a;
			cout<<m.get(a-1)<<'\n';
		}else if(t==2){
			int a,b,v;cin>>a>>b>>v;
			m.rangeup(a-1,b,v);
		}else{
			for(int i=1;i<n+n;++i)cout<<f(i)<<' ';cout<<'\n';
			for(int i=1;i<n+n;++i)cout<<f(i%n+1)<<' ';cout<<'\n';
			for(int i=1;i<n+n;++i)
				cout<<f(m.lazy[i])<<' ';cout<<'\n';
			for(int i=1;i<n+n;++i)
				cout<<f(m.tree[i])<<' ';cout<<'\n';
		}
	}
}
