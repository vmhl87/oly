// Nearest Smallest Value  -  https://cses.fi/problemset/task/1645/
// This is basically just bashable with a set - notice that if we
// traverse backwards along the array, we can mantain a collection
// of elements we have seen, and anytime the next element we look
// at is smaller than any of the elements in our collection, we can
// remove them from the collection.
//
// Example:
//    2 5 1 4 8  {}
//            ^
//  currently the collection is empty; now we advance a step:
//    2 5 1 4 8  {8}
//          ^
//  the collection now contains an 8, and we are looking at a 4, so
//  we can remove the 8 because we have found its nearest smallest
//  value
//    2 5 1 4 8  {4}
//        ^
//  similar here, we can remove the 4 because its nearest smallest
//  value is the 1
//    2 5 1 4 8  {1}
//      ^
//  here we cannot remove the 1 because 5 > 1
//    2 5 1 4 8  {1, 5}
//    ^
//  the 5 can be removed here, but the 1 cannot; both the 2 and 1
//  have no nearest smallest value so they will be represented as
//  a 0 in the output
//
//  To implement we can store the collection in an std::set and
//  use lower_bound to find which elements of the collection to
//  remove at each step.

#include <iostream>
#include <stack>
#include <set>

int main(){
	// the eys trick
	std::cin.tie(0) -> sync_with_stdio(0);
	int n; std::cin >> n;
	// v = values, r = returns
	int v[n], r[n] = {0};
	for(int i=0; i<n; ++i) std::cin >> v[i];
	// collection (set of pairs, each of which storing the value
	// of the element and its position)
	std::set<std::pair<int, int>> q;
	// iterate backwards
	for(int i=n-1; i>=0; --i){
		// use binary search to find the earliest element in the
		// set which is larger than the currently processing one
		auto t = q.lower_bound({v[i]+1, -1});
		// we don't want any weird concurrent modification errors
		// so we store the elements to remove in a stack and then
		// remove them all after traversal
		std::stack<std::pair<int, int>> rem;
		// traverse the collection
		while(t != q.end()){
			// for each of these values, their nearest smallest
			// value is the currently processing one, which is at
			// index i, and with 1-indexing, index i+1.
			r[t->second] = i+1;
			// push onto removal stack
			rem.push(*t);
			++t;
		}
		// remove all elements in stack
		while(rem.size()){
			q.erase(rem.top());
			rem.pop();
		}
		// after we are done processing the current element, add
		// it to the collection
		q.insert({v[i], i});
	}
	// print out returns
	for(int i=0; i<n; ++i){
		if(i) std::cout << ' ';
		std::cout << r[i];
	}
	std::cout << '\n';
}
