// Codeforces round 936 problem E
// We can turn this problem into a graph problem by looking at
// the prefix/suffix maximums not as just maximums, but as
// constraints upon the original permutation. Each prefix maximum
// is guaranteed to be greater than all of the elements before it,
// and the mirror image for the suffix maximums. If we expand some
// test cases, we can see an interesting pattern:
//
// index:      1 2 3 4 5 6
// prefix max: *   *
// suffix max:     *     *
//
// Obviously we can see that element 3 (let's call it a3) is
// greater than a2,a1. However, we can also notice something
// about the elements that are not prefix maximums: a2 is not
// a maximum, meaning, it must be smaller than a1. Similarly,
// a4 and a5 are not suffix maximums, therefore, they must be
// smaller than a6. We can actually show that given all of the
// observations we have made, we can create a "tree" out of the
// six numbers in this example, where the children of a node consist
// of all of the elements that must be smaller than it. For example,
// a3 would be the root of the tree, because it is the global max,
// and the children of a6 would be a4 and a5. Let's draw the tree:
//
//             3
//            / \
//           1   6
//          /   / \
//         2   4   5
//
// Next, we make another observation: The edges on this tree are
// *the only* constraints applied upon the members of the permutation.
// If one element of the tree is a child of another, then the child
// must be smaller than the parent, and if an element is neither
// a child nor a parent of another element, then there may not be
// any constraint applied to that element.
// For example, there is no correlation between a1 and a5. This makes
// sense intuitively, when we look at the inputs.
//
// To find the number of possible permutations that fit our
// constraints, we simply must find a way to distribute the
// numbers 1-n onto this tree such that each edge is satisfied.
// 
// I used a DP-like approach. Notice that each of the child trees
// of a node are completely uncorrelated. Let's look at the example,
// and at node a3: we must distribute the integers 1-5 throughought
// its subtrees. We can notice that because the subtree rooted
// at a1 and the subtree rooted at a6 are completely uncorrelated,
// we can split the integers 1-5 into two groups, one of size 2
// and the other of size 3, and give them to the subtrees.
// This works because each subtree only has to care about the
// "local ordering" of the numbers in its nodes, by that meaning
// it does not need to care about whether or not its nodes are
// bigger or smaller than trees not connected to it.
//
// To calculate this, we need two major components: an implementation
// of binomial coefficients, because those are used to calculate
// the # of ways to split a set of n into a set of k and a set of (n-k),
// and also a factorial implementation, the latter of which is trivial.
//
// There are two stages to the calculation - first we identify the
// root of the tree, which must be equal to both the last prefix max
// and the first suffix max, and then compute the ways to split the
// remaining elements into each side's subtree.
// 
// Then when traversing the subtrees, we can notice that any time that
// the tree splits into several subtrees, at most one of them can have
// a depth greater than one. For example:
//
// index:      1 2 3 4 5 6
// prefix max: * * *     *
// suffix max:           *
//
// The tree is:
//
//              6
//              |
//              3
//             /|\
//            4 5 2
//                |
//                1
// 
// At a3, the tree splits into three subtrees rooted at a4, a5, and a2.
// One of them is structurally different - if we look at the inputs,
// a2 is another prefix maximum, left of a3, whereas a4 and a5 are to
// the right of a3, and we know that they must be smaller than a3
// because they are not prefix maximums. This relationship means
// that they do not have any other subtrees underneath them.
//
// To calculate the number of ways to distribute these subtrees,
// I first calculated the number of ways to distribute the remaining 4
// elements into two sections: one section for the continued tree at a2,
// and the other section for the "ending branches" at a4, a5. Then to
// distribute the "ending branches" among themselves, multiply by
// the factorial of the number of them, which in this case is 2.


#include <iostream>

using ll = long long;
const int M = 1e9 + 7,
		  N = 2e5;


//\\// helper functions
	ll fact[N+1];

	void precomp(){
		fact[0] = 1;

		for(int i=1; i<=N; ++i)
			fact[i] = fact[i-1]*i % M;
	}

	ll inv(ll a){
		ll ret = 1;

		for(ll x=M-2; x; x/=2, a = a*a%M)
			if(x&1) ret = ret*a % M;

		return ret;
	}

	ll nck(int n, int k){
		return fact[n] * inv(fact[k] * fact[n-k] % M) % M;
	}


int pref[N], suff[N];

void test(){
	int n, m1, m2; std::cin >> n >> m1 >> m2;

	for(int i=0; i<m1; ++i) std::cin >> pref[i], --pref[i];
	for(int i=0; i<m2; ++i) std::cin >> suff[i], --suff[i];


	// check for invalid input (first and last elements must be prefix
	// and suffix maximums, and the last prefix max must coincide with
	// the first suffix max)
	if(pref[m1-1] != suff[0] || pref[0] != 0 || suff[m2-1] != n-1){
		std::cout << 0 << '\n';
		return;
	}


	// initial distribution: which elements go to the left of the global
	// maximum, and which go to the right
	ll ret = nck(n-1, suff[0]);


	// process prefix maximums
	for(int i=m1-1; i; --i){
		// how many elements to distribute
		int count = pref[i] - pref[i-1] - 1;

		// partition elements to the left & right
		ret = ret * nck(pref[i]-1, count) % M;
		// permute
		ret = ret * fact[count] % M;
	}


	// similar for suffix maximums
	for(int i=0; i<m2-1; ++i){
		int count = suff[i+1] - suff[i] - 1;

		ret = ret * nck(n-suff[i]-2, count) % M;
		ret = ret * fact[count] % M;
	}

	std::cout << ret << '\n';
}

int main(){
	precomp();

	int t; std::cin >> t;
	while(t--) test();
}
