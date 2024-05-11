// Counting Tilings  -  https://cses.fi/problemset/task/2181/
//
// This problem is pretty cool! Essentially, it is solvable with a
// constructive DP-type approach which sweeps the board from left
// to right (parallel to the short side) and computes the number of
// tilings that, for each configuration of cells in that column,
// the number of tilings that end in such row. It's a bit weird,
// but works out.
//
// We store each column as a binary string (packaged in an int) which
// is 1 for every cell where a "half-domino" sticks out onto the next
// column, and a 0 for every cell where it doesn't.
// For example, this column: (each domino is a <>)
// 		^
// 		v
// 		<
// 		^
// 		v
// 		>
// 		>
// 		<
// would be stored as 00100001, when read from top to bottom.
//
// To transform from one column to the next, we can observe that
// each cell of the initial column with a '1' must be a '0' in the
// next column, because it must be capped by another half-domino
// in the next column. Any segment of 0's will be transformed into
// some sequence that can be built of 00's and 1's.
// For example, 001000011 is valid, whereas 001000101 is not.
//
// This is pretty easy to construct with recursion.

#include <iostream>
using namespace std;

constexpr int M = 1e9 + 7;

// for every possible sequence encoded with <i>, add `a` to all of
// the possible next sequences it can transform into
// i is not purely the binary representation of the column but is
// capped with a 1 - so instead of 0010 it would be 10010, etc.

// to implement this breakdown recursively, this algorithm starts
// at the end of the binary string and "traverses" towards the front,
// processing as it goes. To do this, it continually divides i by 2,
// cutting off the ending bits, and stores the "partial states" in p
// and v.

// a = increment amount, i = state encoding, p = partial state,
// v = place value we are currently looking at, next = loc to write to
void assign(int a, int i, int p, int v, int *next){
	// if we have traversed through all of the state bits in the
	// encoding, all that is left will be the ending cap, which will
	// be 1
	if(i==1){
		// increment the right element of the array - at this point,
		// p is the fully built next state encoding, so it is the
		// index in the array
		next[p] = (next[p] + a) % M; // take modulo
		return;
	}
	// if i ends in a 1, the next state encoding must have a 0 at
	// this bit. We don't modify `p` because adding a 0 at some
	// place value will not change its value. So, we divide i by 2
	// and in turn increase the place value counter.
	if(i&1){
		assign(a, i>>1, p, v<<1, next);
		return;
	}
	// because i did not end in a 1, it ends in a 0. this means that
	// it is possible for the next state encoding to have a 1 in this
	// place. To do this, we of course divide i by 2, and increase the
	// place value counter, but place this 1 bit into `p`: because v
	// has exactly one bit set, in the correct position to be added,
	// we can simply use binary or. (addition works too.)
	assign(a, i>>1, p|v, v<<1, next);
	// if i ends in 00, the next state encoding can also have a 00 here.
	// Because we are skipping 2 places instead of 1, we update i and v
	// accordingly. p stays the same because 0 is insignificant.
	if(!(i&1 || i&2)) assign(a, i>>2, p, v<<2, next);
}

// overload for simpler usage in main
void assign(int a, int i, int *next){
	// if there is nothing to increment then do nothing
	if(a) assign(a, i, 0, 1, next);
}

int main(){
	// input n, m
	int n, m; cin >> n >> m;
	// prepare storage arrays to store & compute states of columns - they
	// must have space to store every possible state, of which there are
	// 2^n of.
	int cur[1<<n] = {0}, next[1<<n] = {0};
	// when computing the first column, we need the "states of the zeroeth
	// column", which really just means that there are zero half-dominoes
	// poking out from that column. (in the finished tiling, no half-dominoes
	// can poke from the first column to the left, so this enforces it.)
	cur[0] = 1;
	// we loop as many times as there are columns
	while(m--){
		// loop over every state in the current column and set it in the next
		for(int i=0; i<1<<n; ++i)
			assign(cur[i], 1<<n|i, next);
		// swap next and cur and reset next
		for(int i=0; i<1<<n; ++i)
			cur[i] = next[i], next[i] = 0;
	}
	// we are only interested in the ending tilings that have zero poking
	// dominoes because we can't have dominoes poke out of the right side
	// either
	cout << cur[0] << '\n';
}
