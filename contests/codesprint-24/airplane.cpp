// Lights, Camera, Airplane  -  https://codesprintla24.kattis.com/contests/codesprintla24highschool/problems/lightscameraairplane


// To better understand the mechanics of the problem, let's consider a
// simpler version.
//
// We have the same tree-like runway structure and lighted paths which
// cycle every takeoff. However, we remove the ramification that some
// of the paths lose power. How can we efficiently determine the number
// of planes that leave every leaf?
//
// Example:
// 							1
// 						   / \
// 						  2   3
// 						     /|\
// 						    4 5 6
//
// We can manually evaluate this a bit and notice a pattern:
//   [2, 5, 2, 4, 2, 6], [2, 5, 2, 4, 2, 6], [2, 5, ...
// 
// Firstly, the pattern repeats every 6 takeoffs. This makes sense,
// because there are 6 possible configurations of the lighted path
// at node 1 and node 3. (2 ways for the lighted path at 1, and 3
// ways at for the lighted path at 3, and multiply)
//
// Furthermore, we can observe the following:
//   Flights leave 2 at turns which are numbered 1 mod 2,
//     4 at turns 4 mod 6,
//     5 at turns 2 mod 6,
//     6 at turns 6 mod 6.
//
// There exists a way to easily construct these without directly
// simulating the flights: Planes leave node 4 anytime that the path
// at 1 points to 2, and the path at 3 points to 4. Using moduli, we
// can represent this as any turn that is 2 mod 2 (for the path at 1)
// and also 1 mod 3 (for the path at 3) and by Chinese Remainder Thm
// we can merge these to get 4 mod 6, which is what we observe!
//
// To compute these moduli programmatically, we can perform some sort
// of traversal like a DFS, and each time we reach a new child node,
// unify the modulus of the parent with the modulus of the parent's
// switcher - in our example, the modulus of node 3 is (2 mod 2), and
// the modulus of its switcher pointing to node 4 is (1 mod 3).


// How do we then account for paths which go out at some point in time?
//
// We can notice that once the path from node c to d goes out, all of
// the planes that would have passed through d will instead end at c.
// This occurs over the interval between when the path from c to d goes
// out, and when the path from c's ancestor to c goes out.
//
// And because we now have a way to determine under which turns a plane
// will pass through any node, this is easy to compute.
// 
// Not only that, but if we use that same DFS that we use to merge
// moduli, we can also use it to calculate for paths going out, online.


#include <iostream>
#include <cmath>
#include <array>
#include <stack>
#include <queue>

#include <stdlib.h>

int gcd(int a, int b){
	if(a < b) return gcd(b, a);
	if(b == 0) return a;
	return gcd(b, a%b);
}

// extended euclidean alg for modular inverses
long long inv(int a, int p){
	int m0 = p, t, q;
	int x0 = 0, x1 = 1;
	if(p == 1) return 0;
	while(a > 1){
		q = a/p, t = p;
		p = a%p, a = t;
		t = x0;
		x0 = x1 - q*x0;
		x1 = t;
	}
	if(x1 < 0) x1 += m0;
	return x1;
}

// 'denominator' aka ending modulus of the union of a mod b and
// c mod d - i couldve wrapped this in a struct, but then it would
// be not possible to use std::array<int, 4> in stack
int crt_d(int a, int b, int c, int d){
	int g = gcd(b, d);
	long long ret = (long long)(b/g) * (long long)d;
	if(ret > 1<<30) return 1<<30;
	return ret;
}

// 'numerator' of the union
int crt_n(int a, int b, int c, int d){
	// compensate for potentially no modulus
	if(a == -1 || c == -1) return -1;

	// overflow compensation - really sketchy
	if(b == 1<<30){
		if(a%d == c%d) return a;
		return -1;
	}

	// b and d not guaranteed to be coprime - determine
	// when there is no valid modulus
	int g = gcd(b, d);
	if(a%g != c%g) return -1;
	// if b is a divisor of d or the other way around, we
	// can avoid computation
	if(g == b) return c;
	if(g == d) return a;

	// if b and d not coprime, find common factors, and attribute them
	// to the modulus base of which they are of higher power:
	// for ex. if we union 7 mod 12 and 13 mod 18, the GCD is 6, and
	// the shared primes are 2, 3. We attribute all of the 2's to the
	// 12 because there are more of them in 12, (4 vs 2) and attrib
	// the 3's to the 18 likewise. This results in the union of 3 mod 4
	// and 4 mod 9, which is mathematically equivalent.
	//     weirdo sqrt complexity but it works
	for(int i=2; i<=g; ++i){
		if(g%i == 0){
			int j = i;
			while(g%(j*i) == 0) j *= i;
			if((b/j)%i != 0) b /= j;
			else if((d/j)%i != 0) d /= j;
			g /= j;
		}else if(i*i > g){
			if((b/g)%g != 0) b /= g;
			else if((d/g)%g != 0) d /= g;
			break;
		}
	}

	// if b and d changed, renormalize
	a %= b, c %= d;

	// apply CRT
	int g1 = gcd(b, c), g2 = gcd(d, a);

	long long i1 = inv(b/g1, d) * (long long)(c/g1),
		 	  i2 = inv(d/g2, b) * (long long)(a/g2);

	// really bad 'debug' technique
//	if(i1 < 0 || i2 < 0) for(;;){}

	// multiply out the terms
	i1 %= d, i2 %= b, i1 *= b, i2 *= d;

	long long o = (long long)b * (long long)d;

	i1 += i2, i1 %= o;

	// if the modulus occurs after 1e9 steps we can ignore it because
	// it will never be relevant in the simulation
	if(i1 > 1<<30) i1 = -1;

	return i1;
}

// debugging the crt was a pain
/*
// graphical printout
void crt(int a, int b, int c, int d){
	std::cout << "(" << a << " mod " << b << ") | (" << c << " mod " << d << ") results in (" <<
		crt_n(a, b, c, d) << " mod " << crt_d(a, b, c, d) << ")\n";
}

// bruteforcer to find failing cases of crt
void testcrt(int t){
	int a = 3 + rand()%20, b = 3 + rand()%20, c = 3 + rand()%20, d = 3 + rand()%20;
	a %= b, c %= d;
	int n = crt_n(a, b, c, d), m = crt_d(a, b, c, d);
	if(n != -1 && (n%b != a || n%d != c))
		std::cout << a << ',' << b << ',' << c << ',' << d << " -> " << n << '|' << m << '\n' <<
			"\t" << n%b << '|' << b << ", " << n%d << '|' << d << "\n\n";
	if(t) testcrt(t-1);
}
*/

int main(){
	int n, t; std::cin >> n >> t;

	// for every node, store the number of planes that fly out of it (ans)
	// and the time in which it is 'removed' from the active tree (del)
	// and its cycle length (mod) and its ancestral node (parent)
	int ans[n] = {}, del[n], mod[n] = {}, parent[n] = {};
	for(int i=0; i<n; ++i) del[i] = t;
	// array of queues to store adjacencies; this simplifies the DFS as
	// we can just check if the adj queue is nonempty and if so pop
	// the front value off of the queue and move to it
	std::queue<int> adj[n];

	// input adjacencies
	for(int i=0; i<n; ++i){
		int r; std::cin >> mod[i];

		for(int j=0; j<mod[i]; ++j)
			std::cin >> r, adj[i].push(r-1), parent[r-1] = i+1;
	}

	// compute deletions
	for(int i=1; i<n; ++i){
		int a, b, c; std::cin >> a >> b >> c;

		// might not be necessary? but here just in case
		if(parent[a-1] == b) b = a;

		del[b-1] = c;
	}

	// DFS stack which stores {index of node, expiration time, cycle represented
	// as a mod b where a, b are the last 2 elements of arr}
	std::stack<std::array<int, 4>> dfs;
	// assume that the root node expires after the t'th query, which means, it
	// stops working before the (t+1)'th query - it also fires every 0 mod 1
	// turns, which means every term
	dfs.push({0, t+1, 0, 1});

	// mostly standard dfs structure
	while(dfs.size()){
		int u = dfs.top()[0],
			e = dfs.top()[1],
			a = dfs.top()[2],
			b = dfs.top()[3];

		if(adj[u].size())
			// push the next node and min the expiry times - if a node's parent
			// expires, no paths will go through the parent, and therefore, nor
			// will they go through the child
			// then use CRT to merge the cycles (i.e. if the parent fires every
			// 1 mod 2 turns and this child is selected every 2 mod 3 turns then
			// the child will overall recieve a plane every 5 mod 6 turns)
			dfs.push({
				adj[u].front(), std::min(e, del[adj[u].front()]),
				crt_n(a%b, b, (mod[u]-adj[u].size()+1)%mod[u], mod[u]),
				crt_d(a%b, b, (mod[u]-adj[u].size()+1)%mod[u], mod[u])
			}), adj[u].pop();

		// if no adjacencies left to add, compute the number of planes that leave
		// this node:
		else{
			// if the # of children (mod) is 0, this is a leaf node, and a plane
			// will leave this node every a mod b turns up until the e'th turn,
			// when this node or some ancestor expires
			// if this node never recieves a plane, its a value will be -1, and
			// it will be meaningless to perform this computation
			if(a != -1 && mod[u] == 0){
				// the cycle of (a mod b) repeats every b turns - and within the
				// turns 1 through e-1, there are (e/1)//b full cycles of b, each
				// of which will result in exactly one plane leaving this node
				ans[u] += (e-1)/b;

				// slight tweak to modulus representation
				if(a == 0) a = b;

				// the last cycle is of length (e-1)%b, and we check if this
				// partial cycle contains (a mod b)
				if((e-1)%b >= a) ++ans[u];
			}

			// next, we consider the number of planes that *would* have routed
			// through this node after it had expired - each of these planes will
			// instead be routed through the parent. We pop off of the dfs stack
			// to access the direct ancestor node.
			dfs.pop();

			// of course, if there is no ancestor, or the previous node never
			// got any traffic in the first place, it is pointless to compute
			if(a != -1 && dfs.size()){
				// u = index of ancestor node
				u = dfs.top()[0];

				// any planes that would have routed through the previous node
				// between the time in which *it* expired and the *ancestor* node
				// expired must have departed at the ancestor node.
				// First we consider the number of full cycles that happened before
				// the ancestor expired, and subtract the number of full cycles that
				// happened before the child expired.
				// Note that `e` still represents the expiration time of the child,
				// and `b` still represents the modulus base of the child, because
				// we are right now considering the planes that *would have routed
				// through the child*, not the ones that would go through ancestor.
				ans[u] += (dfs.top()[1]-1)/b - (e-1)/b;

				if(a == 0) a = b;

				// now we need to consider the two partial cycles - the one that
				// occurs around when the ancestor expires, and the one where the
				// child expires.
				// Around where the ancestor expires, if in this partial cycle
				// the event of (a mod b) is captured by the ancestor, the plane
				// in that cycle will leave at the ancestor.
				if((dfs.top()[1]-1)%b >= a) ++ans[u];

				// In our initial full cycle calculation, we assume that the
				// partial cycle around the child expiration results in the plane
				// leaving at the ancestor. If this is not true, we decrement the
				// count.
				// We do not need to increment the child count, as a similar
				// computation already takes place for the child beforehand.
				if((e-1)%b >= a) --ans[u];
			}
		}
	}

//	int sum = 0;

	for(int i=0; i<n; ++i){
		if(i) std::cout << ' ';
		std::cout << ans[i];
//		sum += ans[i];
	}

	// extremely dumb 'sanity check' debug
//	if(sum < t) for(;;){}

	std::cout << '\n';
}
