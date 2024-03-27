// Annual Ants' Gathering - European Championship 2024
//
// Essentially we can break this question down into a graph contraction
// problem. We can make the observation that we must move all ants
// "below" some house to that house before we move the ants from
// that house, as ants will never move to an empty house. Intuitively,
// this means that we may only move ants that are on leaves.
//
// My solution pretty much simulates exactly that. It is structured
// weirdly because initially I thought I could try to be smart and use
// a segment tree to determine the optimal house to move in O(log n),
// however, this turned out to not work due to a few oversights.
//
// We need some way to pick a contractible leaf, contract it, and update
// the ant counts and adjacencies. We then also must find out which
// houses are now leaves.
//
// The solution I ended up using stores a deque of all active leaves,
// which is appended to when nodes become/are leaf nodes, and is popped
// out of when picking a contractible leaf. Because not all leaves will
// be contractible at a given moment, the queue repeatedly cycles until
// either a contractible node is found, or there is determined to be
// none.

#include <unordered_set>
#include <iostream>
#include <queue>
using namespace std;

// house datastructure
typedef struct{
	// adjacent houses
	unordered_set<int> adj;
	// adjacent houses that are *not leaves yet*
	unordered_set<int> ladj;
	// ant count at this house
	int count=1;
}house;

// solution datastructure - if you look at the commit history
// for this file, you will see that this is essentially a
// repurposed segtree
typedef struct sol{
	// leaf queue & "visited array" to avoid doublecount
	queue<int> leaf;
	vector<bool> leafed;
	// array of houses
	vector<house> houses;
	int n;
	// utility to check of house is leaf
	bool is_leaf(int i){
		return houses[i].adj.size()==1;
	}
	// check if leaf is contractible - compares count with
	// count of only other neighbor, assumes only 1 neighbor
	bool possible(int i){
		return houses[i].count<=houses[*houses[i].adj.begin()].count;
	}
	// try to add a leaf - if it is already leafed, do nothing
	void add_leaf(int i){
		if(leafed[i])return;
		leafed[i]=1;
		leaf.push(i);
	}
	// constructor, also handles input of edges
	sol(int len):leafed(len),houses(len),n(len){
		for(int i=1;i<n;++i){
			int u,v;cin>>u>>v;u--;v--;
			houses[u].adj.insert(v);
			houses[u].ladj.insert(v);
			houses[v].adj.insert(u);
			houses[v].ladj.insert(u);
		}
		// initialize leaves
		for(int i=0;i<n;++i){
			if(is_leaf(i))add_leaf(i);
		}
	}
	// find a contractible leaf, if exists
	int top(){
		// keep track of maximum search length (cycle detection)
		int l=leaf.size();
		for(int i=0;i<l;++i){
			// look at the front of the queue, if does not work,
			// put back onto the queue
			int top=leaf.front();
			leaf.pop();
			if(possible(top))return top;
			else leaf.push(top);
		}
		return -1;
	}
	// relax house i
	void relax(int i){
		// find (assumed to be) only other neighbor
		int other=*houses[i].adj.begin();
		// update counts
		houses[other].count+=houses[i].count;
		// update adjacencies
		houses[i].adj.clear();
		houses[i].ladj.clear();
		houses[other].adj.erase(i);
		houses[other].ladj.erase(i);
		// if the "other leaf" is now a leaf, add it
		if(is_leaf(other))add_leaf(other);
	}
}sol;

int main(){
	// initialize solution datastructure
	int n;cin>>n;
	sol m(n);
	// if there is a valid solution, we will be able
	// to relax n-1 times, so we do exactly that
	for(int i=1;i<n;++i){
		// determine leaf to relax
		int top=m.top();
		if(top<0){
			cout<<"NO\n";
			return 0;
		}
		m.relax(top);
	}
	// if we got through n-1 relaxations then it works
	cout<<"YES\n";
}
