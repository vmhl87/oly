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

// segtree data structure
class segtree{
	private:
		// each node stores maximum free, next, and prev nodes
		struct node{
			int maxfree;
			int next=-1;
			int prev1,prev2;
		};
		// storage
		int hotels;
		vector<node> tree;
		// utility to build a new node from two subnodes i,i+1
		void infill_next(int i,int u){
			// if j is at upper bound, clip
			int j=i+1;if(j==u)j=i;node t;
			// trivially calculate maximum free rooms
			t.maxfree=tree[tree[i].maxfree>tree[j].maxfree?i:j].maxfree;
			t.prev1=i;t.prev2=j;
			// update previous nodes' next indices
			tree[i].next=tree.size();tree[j].next=tree.size();
			tree.push_back(t);
		}
		// utility to reduce the capacity of a hotel and update
		// the whole tree to match
		void set(int i,int v){
			tree[i].maxfree-=v;
			// move upwards from this hotel through the tree
			while(tree[i].next+1){
				i=tree[i].next;
				// update maximum free rooms
				if(tree[tree[i].prev1].maxfree>tree[tree[i].prev2].maxfree)
					tree[i].maxfree=tree[tree[i].prev1].maxfree;
				else tree[i].maxfree=tree[tree[i].prev2].maxfree;
			}
		}
	public:
		// ctor accepts number of hotels and inputs inside itself
		segtree(int n){
			hotels=n;
			tree.reserve(n*2);
			for(int i=0;i<n;++i){
				node t;cin>>t.maxfree;
				tree.push_back(t);
			}
			// l,u = lower,upper bounds
			int l=0,u=n;
			// when they are 1 apart, we have processed the whole
			// tree, because we are now at the root node
			while(l<u-1){
				// iterate over all pairs of nodes within range;
				// if we go out of bounds, we can simply clip
				for(int i=l;i<u;i+=2)
					infill_next(i,u);
				// update ranges
				l=u;u=tree.size();
			}
		}
		// find the first hotel with enough space to hold
		// "min" guests
		int find_hotel(int min){
			// if the tree does not as a whole contain any
			// hotel with enough capacity, simply exit here
			if(tree[tree.size()-1].maxfree<min)return 0;
			// we will start at the root node and traverse
			// downwards, selecting the earliest subnode that
			// has enough capacity
			int ptr=tree.size()-1;
			// if we are looking at a hotel node and not an
			// intermediate node, we are finished
			while(ptr>=hotels){
				// prev1 is guaranteed to be earlier than
				// prev2, by nature of the way the tree
				// unrolls, so we check it first
				if(tree[tree[ptr].prev1].maxfree>=min)
					ptr=tree[ptr].prev1;
				// if it doesn't work, we then use the
				// second vertex
				else ptr=tree[ptr].prev2;
			}
			// update tree to match
			set(ptr,min);
			// our tree is zero-indexed, but the problem wants
			// us to 1-index our answer
			return ptr+1;
		}
};

int main(){
	int n,m;cin>>n>>m;
	// initialize datastructure - it will handle inputting
	// of all the hotels internally
	segtree hotels(n);
	// input guests and process on the fly
	for(int i=0;i<m;++i){
		if(i)cout<<' ';
		int t;cin>>t;
		cout<<hotels.find_hotel(t);
	}
	cout<<'\n';
}
