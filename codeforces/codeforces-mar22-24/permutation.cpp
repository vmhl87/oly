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
using namespace std;
#pragma GCC optimize("Ofast")

#define M 1000000007
#define P 1000000005

// simple factorial with modulus
inline long long fact(long long n){
	long long ret=1,m=M;
	for(unsigned long long i=n;i>1;--i)
		ret=(ret*i)%m;
	return ret;
}

// To calculate binomial coefficients, we use the formula
//                   (n!)/(k!(n-k)!)
// However, we cannot directly compute these numbers, as
// they will far exceed the integer limit. Instead, we use
// a number theory trick, and compute the modular inverse
// of the denominator, and then multiply it to the numerator.
//
// This implementation of modular inverse utilizes Fermat's
// Little Theorem, which states that a^(p-1) will be 1 mod p
// for any prime number p. By the definition of a modular
// inverse, a^(p-2) therefore must be the modular inverse
// of a.  (^ is in this context exponentiation, not XOR)
//
// Implementation utilizes binary exponentiation in order
// to be reasonably performant.
long long inv(long long a){
	long long ret=1;
	for(size_t i=0;i<32;++i){
		if(P&(1<<i))ret=ret*a%M;
		a=(a*a)%M;
	}
	return ret;
}

// Computation of n choose k is relatively trivial - simply
// multiply out the (num)erator and (den)ominator and take
// the modular inverse.
inline long long nck(long long n,long long k){
	long long num=fact(n),den=(fact(k)*fact(n-k))%M;
	return (num*inv(den))%M;
}

int main(){
	unsigned int t;cin>>t;
	while(t--){
		// inputs
		long long n;size_t p,s;
		cin>>n>>p>>s;
		long long ps[p],ss[s];
		for(size_t i=0;i<p;++i)cin>>ps[i];
		for(size_t i=0;i<s;++i)cin>>ss[i];
		// check for invalid input: The first and last elements
		// must be prefix and suffix maximums, respectively,
		// and additionally the last prefix max must be also the
		// first suffix max, as it is the largest overall element.
		if(ps[p-1]!=ss[0]||ps[0]!=1||ss[s-1]!=n){ [[unlikely]]
			cout<<0<<'\n';
			continue;
		}
		// compute the first distribution - out of the remaining
		// n-1 elements, select a section of (max-1) elements
		long long ret=nck(n-1,ss[0]-1);
		// iterate through prefix maximums, and compute "ending branches"
		for(size_t i=p-1;i>0;--i){
			// Compute the distance between this prefix maximum and the
			// next one - if this is more than 1, there are intermediate
			// elements, which will be "ending branches"
			long long diff=ps[i]-ps[i-1]-1;
			if(diff){ [[likely]]
				// The number of total elements to distribute is the
				// number of elements underneath the bigger prefix max
				// minus 1 (the smaller prefix max is guaranteed to be
				// the biggest out of them), and we select the number
				// of "ending branches"
				ret=(ret*nck(ps[i]-2,diff))%M;
				// then multiply by factorial
				ret=(ret*fact(diff))%M;
			}
		}
		// Similar, but for suffix maximums
		for(size_t i=1;i<s;++i){
			long long diff=ss[i]-ss[i-1]-1;
			if(diff){ [[likely]]
				ret=(ret*nck(n-ss[i-1]-1,diff))%M;
				ret=(ret*fact(diff))%M;
			}
		}
		cout<<ret<<'\n';
	}
}
