/*  List Removals

	This problem seems difficult. We can, however, use
	a clever segment tree.
	
	We can build a segment tree that stores the number of
	non-removed elements under each node, and use this
	information to traverse down the tree until we get
	to the correct leaf. We then can print out its value,
	and set its "count" to 0, and then recursively update
	all of its ancestors to match.
	
	We must make an important modification to the segment
	tree in order for this to work - we need the leaves
	to be ordered not from lowest to highest, but rather
	in an order that does not wrap any elements around
	the boundary where there is such.
	
	This approach runs in O(n log n).
*/

#include <iostream>
#include <vector>
using namespace std;

typedef struct segtree{
	// each element is a pair storing nonremoved count
	// and value (only if leaf)
	vector<pair<int,int>> tree;
	int n;
	// propagation is trivial
	void prop(int i){
		tree[i].first=tree[i<<1].first+tree[i<<1|1].first;
	}
	// because we are using a bottom-up implementation, the
	// size of the segment tree is known
	segtree(int len):tree(len*2,make_pair(1,0)),n(len){
		// find shift amount by finding the leftmost boundary
		// of the leaves (highest power of 2 less than or equal
		// to 2n) and subtracting n
		int sh=1;while(sh<(len<<1|1))sh<<=1;sh>>=1;sh-=len;
		// input directly into tree - we use the shift here
		for(int i=0;i<len;++i)
			cin>>tree[(i+sh)%len+len].second;
		// propagate rest of tree
		for(int i=len-1;i>0;--i)prop(i);
	}
	// removal of value v at index i (defaults to root)
	int rem(int v,int i=1){
		// if the node has a set value, it is a leaf,
		// so we update the count to 0 and return
		if(tree[i].second){
			tree[i].first=0;
			return tree[i].second;
		}
		int ret;
		// find which child range is correct
		if(v>tree[i<<1].first)
			ret=rem(v-tree[i<<1].first,i<<1|1);
		else ret=rem(v,i<<1);
		// then propagate and return
		prop(i);
		return ret;
	}
}segtree;

int main(){
	int n;cin>>n;
	segtree m(n);
	for(int i=0;i<n;i++){
		int t;cin>>t;
		cout<<m.rem(t)<<'\n';
	}
}
