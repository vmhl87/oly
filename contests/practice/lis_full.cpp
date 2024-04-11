// Longest Increasing Subsequence
//
// This solution adapts the canonical binary search and replace method
// such that it can print out a valid increasing subsequence of maximal
// length. Because of the way the normal algorithm works, it constructs
// a sequence not necessarily in correct order (because it overwrites
// older values integral to past sequences) but I was able to adapt
// it such that it can retain some form of history.
//
// Somewhat similar to the method used in persistent segtree, we can
// generate some sort of data structure that will let us reconstruct
// the *entire state of the subsequence vector* at the moment any
// node is validly inserted.
//
// We do this by keeping track of, for every inserted element, the
// element that came immediately before it. Trivially we can see that
// the order of these elements will never be violated - the parent of
// an added element will always be "older", and earlier in the sequence.
//
// This requires O(n) space and O(n) total time complexity, and allows
// us to regenerate a *valid subsequence* for any arbitrary element.

#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main(){
	int n;cin>>n;
	// store values and backtrace
	int a[n],back[n];
	// store current sequence
	vector<pair<int,int>> v;
	// main loop - input and process online
	for(int x=0;x<n;++x){
		cin>>a[x];
		// find position to place element
		auto loc=lower_bound(v.begin(),v.end(),make_pair(a[x],0));
		// if place at end, increase length of sequence, and propagate
		// backtrace (current -> vector end OR -1)
		if(loc==v.end()){
			if(v.size())back[x]=v.back().second;
			else back[x]=-1;
			v.push_back(make_pair(a[x],x));
		// otherwise replace an existing value and update backtrace
		}else{
			if(loc==v.begin())back[x]=-1;
			else back[x]=v[(loc-v.begin())-1].second;
			v[loc-v.begin()]=make_pair(a[x],x);
		}
	}
	// output size
	cout<<v.size()<<'\n';
	// traverse though backtrace
	int i=v.back().second;
	stack<int> ret;
	// each processed value is guaranteed to have a parent value, if
	// it is -1, it was placed as the root of the sequence
	while(i>-1){
		ret.push(i);
		i=back[i];
	}
	// sequentially output all
	while(ret.size()){
		cout<<a[ret.top()]<<' ';
		ret.pop();
	}
	cout<<'\n';
}
