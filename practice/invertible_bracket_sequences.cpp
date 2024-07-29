// Invertible Bracket Sequences  -  https://codeforces.com/contest/1976/problem/D
//
// This problem becomes easier if we consider the bracket sequence instead
// as a 2d graph, where each bracket represents the segment between two
// points on the graph: an open bracket represents a segment with increase 1,
// and a close bracket represents a decrease of 1. For example, the sequence
// (()())(()) can be converted to:
//
//      /\/\  /\
//     /    \/  \
//
// We can make some useful observations just from this: First of all, if a
// bracket sequence is valid, that being, each open is matched with a close,
// the sequence must start and end at the same level.
// 
// Furthermore, we can observe that any regular bracket sequence must never
// dip below the level of its endpoints. Why?
// Each bracket in a normal, matched sequence is matched with another bracket
// on the same level as it. This is obvious, because the brackets in between
// the matched pair must also be matched.
// 
// So clearly if any bracket reaches below the level of the endpoints, it
// will not have a valid match, as there wouldn't be another bracket on its
// level on the correct side.
//
// How does inverting work with this representation?
// 
// Inversion literally just causes an inversion of the peaks/valleys:
//
//        /\  /\
//     /\/  \/  \   (inverted the top of the first peak)
//
// Some restrictions are obvious - inversion must occur between two points
// that are on the same level, or it would violate the condition where the
// endpoints must be on the same level. Secondly the inversion may not cause
// any part of the graph to go below the level of the endpoints.
//
// Consider the following initial sequence:
//
//       /\
//      /  \
//     /    \
//
// If we invert the top 2 thirds of the sequence, part of it will clearly go
// below the endpoints:
//
//     /\  /\
//       \/
//
// For any inversion, if the heights of its boundaries are h, it will only
// remain valild post-inversion if no section of the sequence being inverted
// was originally more than h*2 in height. In this example of invalidity,
// h = 1, and there was a peak initially of height 3.
//
// So, we can do a segtree range query to determine validity of ranges.
// The next useful observation is that if a range [l, r] works, the range
// [l, r-1] will work, provided r-1 is not less than l. So, to determine, for
// some left endpoint l the number of valid right endpoints, we can binary
// search on all possible right endpoints with matching height.
//
// Implementing this is pretty easy with some map compression and other things.

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <map>

void test_case(){
	std::string s; std::cin >> s;

	// s.length() segments, so s.length()+1 points between them
	int n = s.length()+1;

	// heights array
	int heights[n]; heights[0] = 0;

	// mapping from height -> location vector;
	// makes binary searching for right endpoints easier
	std::map<int, std::vector<int>> loc;

	// traverse segments and update arrays+map kinda cursed fr
	for(int i=0; i<n-1; ++i){
		loc[heights[i]].push_back(i);

		if(s[i] == '(') heights[i+1] = heights[i] + 1;
		else heights[i+1] = heights[i] - 1;
	}

	// build segtree
	int tree[n<<1];
	for(int i=0; i<n; ++i) tree[i+n] = heights[i];
	for(int i=n-1; i; --i) tree[i] = std::max(tree[i<<1], tree[i<<1|1]);

	long long res = 0;

	// keep track of which left endpoint we are at within each
	// map entry etc kinda scuffed but wtv
	std::map<int, int> pos;

	for(int i=0; i<n; ++i){
		// allowed max height = h*2
		int max = heights[i] << 1;

		// binary search over positions in loc[h]
		int ol = pos[heights[i]]++, r = loc[heights[i]].size()-1;
		int l = ol;

		while(l < r){
			int mid = (l + r + 1) >> 1;

			// segtree query for range of sequence
			int d = i, u = loc[heights[i]][mid]+1, ret = 0;

			// mostly standard
			for(d += n, u += n; d < u; d >>= 1, u >>= 1){
				if(d & 1) ret = std::max(ret, tree[d++]);
				if(u & 1) ret = std::max(ret, tree[--u]);
			}

			// binsearch
			if(ret > max) r = mid-1;
			else l = mid;
		}

		// compute valid right endpoints
		res += (long long)l - (long long)ol;
	}

	std::cout << res << '\n';
}

int main(){
	int t; std::cin >> t;

	while(t--) test_case();
}
