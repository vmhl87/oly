// Josephus Problem 2  -  https://cses.fi/problemset/task/2163/
// I realized that this problem is essentially isomorphic to
// List Removals: we basically need to be able to locate and remove
// an arbitrary element of a list, and update the rest of it.
// This is an experimental version that uses a set and cursed
// binary search instead of a) a segtree or b) ordered_set

#include <iostream>
#include <set>

int main(){
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int n, k; std::cin >> n >> k;
	// try out a set with cursedness
	std::set<int> childs;
	for(int i=0; i<n; ++i) childs.insert(i+1);
	// starts at position 0
	int at = 0;
	// s = ring size (# of children remaining)
	for(int s=n; s>0; --s){
		if(s < n) std::cout << ' ';
		// advance position, skip k children
		at = (at + k) % s;
		// find position in set or smth
		int l = 1, r = n+1;
		// really cursed binary search
		while(l < r-1){
			int m = (l+r)>>1;
			int dist = std::distance(
					childs.begin(),
					childs.lower_bound(m)
				);
			if(at < dist) r = m;
			else l = m;
		}
		// print and update
		std::cout << l;
		childs.erase(l);
	}
	std::cout << '\n';
}
