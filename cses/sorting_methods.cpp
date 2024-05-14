// Sorting Methods  -  https://cses.fi/problemset/task/1162/
// Each sorting method is essentially implemented on its own, so their
// documentation is with each one.

// ordered set
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
#define oset __gnu_pbds::tree<int, __gnu_pbds::null_type, std::less<int>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>

#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

// The first method is essentially bubble sort - and we simulate it by
// bubbling downwards the 1 to the beginning, then the 2 to the second
// position, etc. This is obviously too slow to simulate.
// We can make the observation that at the point in time when we start
// bubbling number n to its desired position, it will have to move by
// index[n] - n spaces, where index[n] denotes its (1-indexed) position
// in the array at this point in time.
// ex:
//     3 5 2 1 4
//     <------
//     1 3 5 2 4
//       <----
//     1 2 3 5 4
//           <--
//     1 2 3 4 5
// The implementation is not quite this simple because as numbers less
// than n will be bubbled down, the index of n will increase. In our
// example, the 3 initially starts at index 1, but ends up in index 3
// after the 1 and 2 are shifted before it. So to calculate the amount
// each value will need to move, we take its initial index and add the
// number of values ahead of it which are smaller than it. In our
// example, the 3 has two values ahead of it smaller than it (1,2) so
// its effective index is increased by two. To compute this, we can
// iterate backwards through the array, mantaining an ordered set such
// that while looking at index n, all of the values in indexes n+1 and
// up are in the ordered set, and with binary search we can determine
// how many of those values are less than the value at n.
// ex:
//     3(5)2 1 4   <- we are looking at the value 5
//     oset: {1, 2, 4} -> 3 elements smaller than 5
//     final index = 2 + 3 = 5
inline long long bubble_sort(int n, int *p){
	int index[n];
	oset s;
	
	for(int i=n-1; i>=0; --i){
		// shift distance
		int dist;

		// use binary search to find the first element in s that is
		// larger than p[i] - the number of elements before it will
		// be the shift amount
		auto x = s.lower_bound(p[i]);
		// if all elements are less than p[i], we get an iterator to
		// the end of the set, but .order_of_key won't work on that,
		// so we manually set to the size of the set.
		if(x != s.end()) dist = s.order_of_key(*x);
		else dist = s.size();

		// set final index
		index[p[i]-1] = i+dist;

		// mantain ordered set
		s.insert(p[i]);
	}

	// compute the final number of swaps
	long long swaps = 0;
	for(int i=0; i<n; ++i) swaps += index[i] - i;
	return swaps;
}

// To sort by swapping, we can notice that it is sufficient to
// simply swap the 1 to the first position, then the 2 to the
// second, etc, similarly to how we optimized bubblesort.
// This one, however, we can just simulate.
inline int swap_sort(int n, int *p){
	// r = mutable location array, c = inverse mapping
	// To efficiently determine where the 1, 2, 3, etc. are so
	// that we can swap them, we use an array to store the
	// inverse mapping - that being, if r[1] = 3, then c[3] = 1.
	int ret = 0, r[n], c[n];
	// fill both arrays (we don't want to modify p, because the
	// other sorts will use it)
	for(int i=0; i<n; ++i) r[i] = p[i]-1, c[p[i]-1] = i;
	
	// we simply iterate forwards and swap if necessary
	for(int i=0; i<n; ++i) if(r[i] != i){
		++ret;

		// this has a lot going on - we'll break it up:
		//   c[i] = old position of i
		//   r[i] = current value at position i
		//   r[c[i]] = value at old position of i
		//   c[r[i]] = position of current value at position i
		// First, whatever value used to be set to i, we overwrite
		// with the value currently at index i.
		//   for ex:
		//     (5)2 3 4[1]   <- () denotes position i, [] denotes
		//                      position of i
		//   after overwrite:
		//     (5)2 3 4[5]
		// Next, we update the inverse mapping, so that we know the
		// 5 is at position 5 instead of at position 1 like it was.
		r[c[i]] = r[i], c[r[i]] = c[i];
	}

	return ret;
}

// For move sort, we can observe that the upper bound on the # of
// moves required is n, (as we simply move each element to its
// correct place), and we can make the further observation that
// the maximum number of elements that we can avoid moving is the
// length of the longest increasing subsequence of the sequence.
// In the sample case, the LIS of 7 8 2 6 5 1 3 4 is the [1 3 4]
// portion, and therefore all other 5 elements must be moved.
inline int move_sort(int n, int *p){
	// We do the classic O(n log n) LIS implementation using
	// binary search through a vector.
	std::vector<int> lis;

	for(int i=0; i<n; ++i){
		// find the first element larger than p[i] in the vector,
		// if all elements are smaller than p[i] we push it to the
		// end, otherwise, we set that element to p[i].
		auto x = std::lower_bound(lis.begin(), lis.end(), p[i]);
		if(x == lis.end()) lis.push_back(p[i]);
		else lis[x - lis.begin()] = p[i];
	}

	return n - lis.size();
}

// Trivially we can fully sort the array by just sending n to
// the front, then n-1, then n-2, etc. To optimize this, we must
// find values we can avoid swapping. Logically, if we swap k+1
// to the front, and also k-1 at some point after that, we must
// swap k to the front between the two. The only elements that
// we can avoid swapping are the ones from n, n-1, etc.
// Essentially, we must find the smallest k such that k is before
// k+1 in the array, k+1 is before k+2, etc.
inline int front_sort(int n, int *p){
	// To find such a sequence, we simply iterate backwards
	// through the array and find the sequence as we go.
	// The target value starts at n, and the total number of moves
	// starts at n and counts down each time we encounter our target.
	int target = n, ret = n;

	for(int i=n-1; i>=0; --i)
		// not only do we decrease target, but also # of
		// moves necessary.
		if(p[i] == target) --target, --ret;

	return ret;
}

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int n; std::cin >> n;

	int p[n];
	for(int i=0; i<n; ++i) std::cin >> p[i];

	// Because bubble sort has an upper bound of n^2 moves, we
	// need to store in a 64-bit integer
	long long s1 = bubble_sort(n, p);
	int s2 = swap_sort(n, p),
		s3 = move_sort(n, p),
		s4 = front_sort(n, p);

	std::cout << s1 << ' ' << s2 << ' ' << s3 << ' ' << s4 << '\n';
}
