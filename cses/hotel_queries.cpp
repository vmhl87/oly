/*  Hotel Queries  -  https://cses.fi/problemset/task/1143

	We need an efficient way to find the first value
	of an array greater than or equal to a target
	value, and to be able to repeat this multiple times.
	
	I used a segment tree - not in the simpler sense of
	finding the overall maximum or minimum, but rather to
	break down the hotels into a series of ranges, which
	can be easily checked to contain or not contain
	the element we want.
	
	Each node of a segment tree corresponds to a range of
	hotels, and in my implementation it stores the maximum
	number of guests that can be stored in any one hotel in
	that range. This is useful, because if a range's max
	over all hotels is less than the number of guests, we can
	discard the entire range.
	
	Also, because the order of elements is retained in a
	binary segment tree, I can use the tree to also find the
	first hotel with enough space. Each time I am at a node,
	I can simply choose the first sub-node which has a hotel
	with enough capacity. This is simple to check, because a
	range of hotels with overall maximum free rooms above
	the number of guests is guaranteed to have at least one
	hotel with enough rooms to fit our guests.
	
	Updating the amount of free rooms once we have found a
	suitable hotel is similarly doable in log(n) time.
*/

#include <iostream>
#include <vector>
using namespace std;

// Because we only will have one segtree instance, it is
// cleaner to use a namespace-based impl rather than a struct
namespace seg{
	// tree stores maximum free rooms in any single hotel within
	// entire subtree of node
	vector<int> tree;
	// n = length, s = wraparound boundary (due to bottom-up impl
	// we need to account for wrap/unwrap when parse)
	int n,s;
	// propagate node upwards (pretty standard for my impl)
	void prop(int i){
		tree[i]=max(tree[i<<1],tree[i<<1|1]);
	}
	// wraparound - because we do care about the order of the
	// hotels, and want to always pick the earlier hotels first,
	// we must mantain some sort of ordering
	int leaf(int i){
		return n+(s+i)%n;
	}
	int unleaf(int i){
		return (i-s+n)%n;
	}
	// not a struct, so no ctor
	void init(int len){
		n=len;s=1<<__lg(n+n-1);
		tree.resize(n*2);
		// input on the fly
		for(int i=0;i<n;++i)cin>>tree[leaf(i)];
		for(int i=n-1;i>0;--i)prop(i);
	}
	// find first hotel with at least v free rooms
	int find(int v){
		// fail condition - no room has enough space
		if(tree[1]<v)return 0;
		// i = node currently searching, starts at root
		int i=1;
		while(i<n){
			// if the left (smaller) branch is possible, we will
			// always pick it
			if(tree[i<<1]>=v)i<<=1;
			else i=i<<1|1;
		}
		// find original id of this hotel and 1-index
		int ret=unleaf(i)+1;
		// change and propagate back up
		tree[i]-=v;
		while(i){
			i>>=1;prop(i);
		}
		return ret;
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,m;cin>>n>>m;
	// initialize datastructure - it will handle inputting
	// of all the hotels internally
	seg::init(n);
	// input guests and process on the fly
	for(int i=0;i<m;++i){
		if(i)cout<<' ';
		int t;cin>>t;
		cout<<seg::find(t);
	}
	cout<<'\n';
}
