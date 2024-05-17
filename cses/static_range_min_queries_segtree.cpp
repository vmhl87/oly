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
	int cm(int a,int b){
		if(a<0)return b;
		return min(a,b);
	}
	int range(int l,int r){
		l+=n;r+=n-1;
		int ret=-1;
		while(l<=r){
			if(l&1)ret=cm(ret,tree[l++]);
			if(~r&1)ret=cm(ret,tree[r--]);
			l>>=1;r>>=1;
		}
		return ret;
	}
}segtree;

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);
	int n,q;cin>>n>>q;
	segtree m(n);
	for(int i=0;i<q;i++){
		int a,b;cin>>a>>b;
		cout<<m.range(a-1,b)<<'\n';
	}
}
