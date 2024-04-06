#include <iostream>
#include <vector>
#include <queue>
using namespace std;

namespace seg{
	struct segtree{
		vector<int> tree;
		int n;
		void cpy(segtree a,segtree b){
			n=a.n;
			tree.resize(n*2);
			for(int i=0;i<n*2;++i)
				tree[i]=a.tree[i]+b.tree[i];
		}
		void init(int l){
			n=l;tree.resize(l*2);
			for(int i=0;i<n;++i){
				char c;cin>>c;
				tree[i+n]=(c=='*');
			}
			for(int i=n-1;i>0;--i)
				tree[i]=tree[i<<1]+tree[i<<1|1];
		}
		void set(int i,int v){
			i+=n;
			while(i){
				tree[i]+=v;
				i>>=1;
			}
		}
		int range(int l,int r){
			l+=n;r+=n;
			int ret=0;
			while(l<r){
				if(l&1)ret+=tree[l++];
				if(r&1)ret+=tree[--r];
				l>>=1;r>>=1;
			}
			return ret;
		}
	};
	vector<segtree> tree;
	int n;
	void init(int l){
		n=l;
		tree.resize(l*2);
		for(int i=0;i<n;++i)tree[i+n].init(l);
		for(int i=n-1;i>0;--i)
			tree[i].cpy(tree[i<<1],tree[i<<1|1]);
	}
	void flip(int x,int y){
		y+=n;
		int diff=1-(tree[y].tree[x+n]<<1);
		while(y){
			tree[y].set(x,diff);
			y>>=1;
		}
	}
	int range(int y1,int x1,int y2,int x2){
		y1+=n;y2+=n;
		int ret=0;
		while(y1<y2){
			if(y1&1)ret+=tree[y1++].range(x1,x2);
			if(y2&1)ret+=tree[--y2].range(x1,x2);
			y1>>=1;y2>>=1;
		}
		return ret;
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,q;cin>>n>>q;
	seg::init(n);
	while(q-->0){
		int t;cin>>t;
		if(t-1){
			int x1,y1,x2,y2;cin>>y1>>x1>>y2>>x2;
			cout<<seg::range(y1-1,x1-1,y2,x2)<<'\n';
		}else{
			int x,y;cin>>y>>x;
			seg::flip(x-1,y-1);
		}
	}
}
