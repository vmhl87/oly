// Josephus Problem I  -  https://cses.fi/problemset/task/2162/
// This is pretty trivial by simulation. We keep a "linked ring list"
// stored in an array (item -> index) and store a counter of which child
// we are currently at.

#include <iostream>

int main(){
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int n; std::cin >> n;
	// each element of the array is the index of the child after them
	int r[n];
	for(int i=1; i<n; ++i) r[i-1] = i;
	r[n-1] = 0;
	// currently at the first child
	int at = 0;
	// each iteration we remove a child, therefore, n iterations
	for(int i=0; i<n; ++i){
		// space separation idk
		if(i) std::cout << ' ';
		// store old position
		int o = at;
		// advance current position
		at = r[at];
		// print out child to remove
		std::cout << at+1;
		// advance position
		at = r[at];
		// link previous position to current
		r[o] = at;
	}
	std::cout << '\n';
}
