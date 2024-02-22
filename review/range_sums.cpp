// import standard library (used for vector)
#include <bits/stdc++.h>
// namespace from std class (this is complicated but dw)
using namespace std;
// I think this macro returns the length of a vector but I am not fully sure
#define sz(x) (int)size(x)
// basically a typedef
using ll = long long;
// vector of long long (vector is a variable length array essentially)
using vl = vector<ll>;
/*
Here we create a function that builds a partial sum from an input vector
and returns the built vector
	We can see that the function returns type `v1`, which we can see is a
	shortening for `vector<long long>`, aka a variable length array of
	64-bit integers
	The argument for this function is a single vector of 64 bit integers,
	which serves as the initial numbers to calculate the partial sum of
	the & symbol serves as an explicit declaration that `a` is a pointer,
	though even if you don't include that it'll be assumed to be a pointer.
	const is probably for some memory optimization stuff
*/
v1 psum(const vl &a) {
	// create output vector
	// syntax for creating vectors is usually:
	//     vector<datatype> varname(length);   note that `length` is optional
	// and here we allocate the number of elements of the vector + 1,
	// because the partial sum will have 1 extra element
	vl psum(sz(a) + 1);
	// iterate over the elements of the input vector `a` and update the
	// new array of partial sums as follows:
	//     partial sum n+1 is the sum of partial sum n and the nth element
	//     of the input vector `a`; we can see here that psum[0] is never
	//     explicitly set and this is because `vector<>` automatically
	//     fills a created vector with zeroes when created
	for(int i=0; i<sz(a); ++i) psum[i+1] = psum[i] + a[i];
	// pass back the computed partial sum vector
	return psum;
}
// main function (execution jumps to this location when program is run)
int main() {
	// declare N and Q, which serves the purpose of allocating enough memory
	// to store these two variables
	int N, Q;
	// read from standard input and set values of N and Q
	cin >> N >> Q;
	// allocate a `vector<long long>` with N elements
	vl a(N);
	// this is what is called a foreach loop - it iterates through every
	// element of an array-like object rather than incrementing a variable
	// in this case, it iterates over all elements of `a`, and assigns their
	// memory address (pointer) to the local variable `x`, which can be set
	// by reading from standard input (cin)
	for(ll &x : a) cin >> x;
	// allocate a 64-bit integer vector and compute the partial sums of
	// `a` into this newly created vector
	vl p = psum(a);
	// in this for loop, `i` does not actually serve any purpose other than
	// iterating such that the loop runs Q times
	for(int i=0; i<Q; ++i) {
		// declare two integers and allocate space for them
		int l, r;
		// read from standard input and set `l`, `r`
		cin >> l >> r;
		// write through standard output the difference of two partial sums
		// which we query from the partial sum vector `p`
		cout << p[r] - p[l] << '\n';
	}
	// no explicit `return 0` statement because it is assumed
}
