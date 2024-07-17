// The World Is Just A Programming Task  -  https://codeforces.com/contest/1239/problem/B
// 
// Mountain representation is very helpful for this problem.
// Recall the following:
//   A bracket sequence is valid if and only if its mountain
//   represntation 1) starts and ends at the same elevation,
//   and 2) at no point dips below its starting elevation.
//
// How can we use this to determine valid cyclic shifts?
// Consider the following sequence:
//   (()(()))()
//
//       /\
//    /\/  \
//   /      \/\
//
// Say that we shift right by 3 brackets. We get:
//   (()))()(()
//
//    /\
//   /  \    /\
//       \/\/
//
// This isn't a valid sequence. Though, we can see something
// interesting: the elevation of the start and end here is
// equal to the elevation of the location in the original
// sequence in which we split, and the number of points at
// each elevation is unchanged.
//
// We can therefore show the following: The number of valid
// cyclic shifts in some valid bracket sequence is equal to
// the number of points in which the sequence touches the
// minimum elevation point.
//
// How does the heightmap change when we swap brackets?
// For example, let's take the simple sequence ((())) and
// swap the 2nd and 5th brackets.
//
//   ((())) -> ()()()
//
//     /\
//    -  -  -> /-/\-\
//   /    \
//
// Swapping a pair of brackets either increases or decreases
// the height of the enclosed segment by 2.
//
// So, we just need to determine the optimal section to shift
// in order to maximize the number of points of minimal elevation.
// There are a couple of cases we can break it into:
//
// 1. Shift up all points of minimum elevation, so that the new
//    lowest level is min+1. ex:
//
//      ())(() -> ()()()
//
//      /\  /\ -> /\/\/\
//        \/
//
// 2. Shift up all points of elevation min+1 and min, so the new
//    lowest is min+2:
//
//      )))((( -> )()()(
//
//      \    /
//       \  /  -> \/\/\/
//        \/
//
// 3. Shift down some section of min+1 (and no min), becoming the
//    new lowest elevation:
//
//      (()()) -> )()()(
//
//       /\/\  -> \/\/\/
//      /    \
//
// 4. Shift down a section of min+2, and no min+1 or min, making
//    these points part of the lowest elevation section:
//      
//      ((()())) -> ()()()()
//
//        /\/\
//       /    \  -> /\/\/\/\
//      /      \
//
// These are basically all computable using 2 pointer.

#include <iostream>

// accumulated height map
int heights[300001];

int main(){
	int n; std::cin >> n;

	// fill heightmap and compute min; pretty messy
	int h = 0, min = 0;
	for(int i=0; i<n; ++i){
		char c; std::cin >> c;
		h += (c == '(' ? 1 : -1);
		min = (h < min ? h : min);
		heights[i+1] = h;
	}

	// Process the one failing case: If the sequence
	// does not initially start and end at the same
	// elevation, no amount of swaps or shifts will
	// result in a valid sequence. The start elevation
	// is always 0, so check against that.
	if(heights[n] != 0){
		std::cout << "0\n1 1\n";
		return 0;
	}

	// Try to shift up minimum section, making min+1 the new
	// lowest elevation:
	// First count number of [min+1]
	int l1 = 0;
	for(int i=0; i<n; ++i) if(heights[i] == min+1) ++l1;
	
	// Then do a goofy blockparsing thing to grab all
	// intervals bounded by [min] and determine how many
	// levels of [min+1] they remove
	int part = 0, init = 0, s1, e1;
	for(int i=0; i<=n; ++i){
		if(heights[i] == min+1) ++part;
		if(heights[i] == min){
			// first block doesn't count
			if(init) l1 -= part;
			else s1 = i;
			e1 = i, init = 1, part = 0;
		}
	}

	// This trips up when the start value is min elevation
	if(s1 == 0) l1 = -1;

	// Shift up all min+1, so min+2 is new lowest; this
	// also converts all min to min+2
	// Start by counting number of [min+2]
	int l2 = 0;
	for(int i=0; i<n; ++i) if(heights[i] == min+2) ++l2;

	// Use similar block parser to find all intervals
	// bounded by [min+1] and see how they affect result
	part = 0, init = 0;
	int s2, e2;
	for(int i=0; i<=n; ++i){
		if(heights[i] == min+2) ++part;
		if(heights[i] == min) --part;
		if(heights[i] == min+1){
			if(init) l2 -= part;
			else s2 = i;
			init = 1, e2 = i, part = 0;
		}
	}

	// Same issue with starting value
	if(s2 == 0) l2 = -1;

	// Shift down some optimal section of [min+1] which
	// contains no [min] - will make new lowest level
	// Same block parser, but grab blocks bounded by
	// [min] and count number of [min+1]
	int l3 = 0, ps;
	part = 0, init = 0;
	int s3, e3;
	for(int i=0; i<=n; ++i){
		if(heights[i] == min+1) ++part;
		if(heights[i] == min){
			if(init){
				// optimal section thing
				if(part > l3){
					l3 = part;
					s3 = ps, e3 = i;
				}
			}
			init = 1, ps = i, part = 0;
		}
	}

	// Shift down [min+2] in segments without any [min+1]
	// or [min]; add these to # of [min]
	// Count initial amt
	int l4 = 0;
	for(int i=0; i<n; ++i) if(heights[i] == min) ++l4;

	// Block parser again
	part = 0, init = 0;
	int s4 = 0, e4 = 1, best = 0;
	for(int i=0; i<=n; ++i){
		if(heights[i] == min+2) ++part;
		if(heights[i] == min || heights[i] == min+1){
			if(init) if(part > best){
				best = part;
				s4 = ps, e4 = i;
			}
			init = 1, ps = i, part = 0;
		}
	}
	l4 += best;

	// Find best result and print out
	int opt = std::max(std::max(l1, l2), std::max(l3, l4));

	if(opt == l1) std::cout << l1 << '\n' << s1 << ' ' << e1+1 << '\n';
	else if(opt == l2) std::cout << l2 << '\n' << s2 << ' ' << e2+1 << '\n';
	else if(opt == l3) std::cout << l3 << '\n' << s3+1 << ' ' << e3 << '\n';
	else if(opt == l4) std::cout << l4 << '\n' << s4+1 << ' ' << e4 << '\n';
}
