// Forest Queries II  -  https://cses.fi/problemset/task/1739/
// Quite literally just an application of 2d nonlazy segtree
#include <iostream>
#include <vector>
using namespace std;

// main segtree is namespaced because it is single-instanced,
// however, each "row segtree" must be a datastruct as it will
// be mulit-instanced
namespace seg{
	// each node of main tree is a segtree representing the sums
	// on each row or collection of rows
	struct segtree{
		// stores # of trees under node in row
		vector<int> tree;
		int n;
		// when initializing intermediate nodes of segtree, simply
		// sum up values at every node, no need to propagate
		void cpy(segtree a,segtree b){
			n=a.n;
			tree.resize(n*2);
			for(int i=0;i<n*2;++i)
				tree[i]=a.tree[i]+b.tree[i];
		}
		// initialize a leaf of main tree, handles input itself
		void init(int l){
			n=l;tree.resize(l*2);
			for(int i=0;i<n;++i){
				char c;cin>>c;
				tree[i+n]=(c=='*');
			}
			for(int i=n-1;i>0;--i)
				tree[i]=tree[i<<1]+tree[i<<1|1];
		}
		// shift position i by some delta v (guaranteed to be +-1)
		void set(int i,int v){
			i+=n;
			while(i){
				tree[i]+=v;
				i>>=1;
			}
		}
		// find # of trees in range [l,r)
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
	// main tree is a collection of segtrees - even intermediate nodes
	// are segtrees themselves, so we can range query efficiently
	vector<segtree> tree;
	int n;
	// init main tree
	void init(int l){
		n=l;
		tree.resize(l*2);
		// we call init() on the leaves so that they populate with
		// the proper values
		for(int i=0;i<n;++i)tree[i+n].init(l);
		// we do not have a prop() method like my standard segtree
		// impl because we can simply copy the values over once,
		// flip/set queries do not use prop() because of efficiency
		for(int i=n-1;i>0;--i)
			tree[i].cpy(tree[i<<1],tree[i<<1|1]);
	}
	// flip tree at (x,y)
	void flip(int x,int y){
		y+=n;
		// compute delta - if (x,y) = 0 then 1 else -1
		int diff=1-(tree[y].tree[x+n]<<1);
		// apply this delta over all sub-trees containing (x,y)
		while(y){
			tree[y].set(x,diff);
			y>>=1;
		}
	}
	// count # of trees over rectangular range
	int range(int y1,int x1,int y2,int x2){
		y1+=n;y2+=n;
		int ret=0;
		// pretty standard impl - for every subtree that sums to
		// the final range, add its sub-sum
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
	// this one func does all of the init we need
	seg::init(n);
	// pretty self explanatory
	while(q--){
		int t;cin>>t;
		if(t&1){
			int x,y;cin>>y>>x;
			seg::flip(x-1,y-1);
		}else{
			int x1,y1,x2,y2;cin>>y1>>x1>>y2>>x2;
			cout<<seg::range(y1-1,x1-1,y2,x2)<<'\n';
		}
	}
}
