// Concert Tickets  -  https://cses.fi/problemset/task/1091/
//
// This problem is very similar to List Removals in that we want
// to pick and remove certain elements from a sorted list while
// still being able to use some sort of binary search-type alg
// upon it. I decided to use a segment tree, which could emulate
// the binary search-type algorithm by keeping track at each node
// of the range of values contained underneath it, and mantaining
// sorted order at every step.

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Tried out a namespace-based segment tree because it is better
// memory-wise than a struct-based one, and we are only using it
// one time, unlike CF-style multiple test cases
namespace seg{
	// store min,max at each node
	vector<pair<int,int>> tree;
	// n = length, ln = index of wraparound point (I am using the
	// bottom-up segtree implementation so to mantain proper sorted
	// order I must account for wraparound properly)
	int n,ln=1;
	void prop(int i){
		// note that this still works with the 'removed' values
		// because I set .s to -1 and .f to 1<<30 (essentially inf)
		tree[i].first=min(tree[i<<1].first,tree[i<<1|1].first);
		tree[i].second=max(tree[i<<1].second,tree[i<<1|1].second);
	}
	// find tree index of each element, accounting for wrap
	int leaf(int i){
		return n+(ln-n+i)%n;
	}
	// initialize from vector
	void init(vector<int> v){
		tree.resize(v.size()<<1);
		// compute wraparound - always a power of 2
		n=v.size();while(ln<=n)ln<<=1;
		for(int i=0;i<n;++i)tree[leaf(i)]=make_pair(v[i],v[i]);
		for(int i=n-1;i>0;--i)prop(i);
	}
	// find optimal ticket to satisfy bound `v`
	int opt(int v){
		// the only fail condition is that there does not exist
		// any ticket with price satisfying bound, in other words,
		// the global minimum ticket price is > v
		if(v<tree[1].first)return -1;
		// traverse down the tree and take the optimal branch
		int i=1;
		while(i<n){
			// select the left (guaranteed lower) branch if and
			// only if the right branch does not have any tickets
			// meeting bound `v` - we do not need to worry about
			// picking earlier rather than later values if repeats
			// because the ranges stored at each node will only
			// contract and never expand
			if(tree[i<<1|1].first>v)i<<=1;
			else i=i<<1|1;
		}
		int ret=tree[i].second;
		// 'virtual delete' selected node
		tree[i].first=1<<30;
		tree[i].second=-1;
		// full propagate (this does touch 0, but whatever)
		while(i){
			i>>=1;prop(i);
		}
		return ret;
	}
}

int main(){
	int n,m;cin>>n>>m;
	vector<int> h(n);
	for(int i=0;i<n;++i)cin>>h[i];
	// segtree must always be sorted
	sort(h.begin(),h.end());
	// namespace-based segtree has the very cool property that
	// the tree can be directly accessed as seg::tree
	seg::init(h);
	for(int i=0;i<m;++i){
		int t;cin>>t;
		// as simple as that!
		cout<<seg::opt(t)<<'\n';
	}
}
