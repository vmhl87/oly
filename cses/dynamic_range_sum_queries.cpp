#include <iostream>
#include <vector>
using namespace std;

typedef struct segtree{
	vector<long long> tree;
	int n;
	void prop(int i){
		tree[i]=tree[i<<1]+tree[i<<1|1];
	}
	segtree(int len):tree(len*2),n(len){
		for(int i=0;i<len;++i)
			cin>>tree[i+n];
		for(int i=len-1;i>0;--i)prop(i);
	}
	void set(int i,long long v){
		i+=n;
		long long dif=v-tree[i];
		while(i){
			tree[i]+=dif;
			i>>=1;
		}
	}
	long long range(int l,int r){
		l+=n;r+=n-1;
		long long ret=0;
		while(l<=r){
			if(l&1)ret+=tree[l++];
			if(~r&1)ret+=tree[r--];
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
		if(t&1)m.set(a-1,(long long)b);
		else cout<<m.range(a-1,b)<<'\n';
	}
}
