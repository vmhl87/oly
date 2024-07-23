// CCC '18 S5 Maximum Strategic Savings  -  https://dmoj.ca/problem/ccc18s5
//
// This problem reeks of MST :P
//
// We have some sort of graph with patterned edges of certain
// weight, and want to minimize sum of weights. Unfortunately,
// we can't use literal MST because there are something on
// the order of 1e10 edges, so we need to exploit the patterning.
//
// For the sake of understanding, let's use standard MST, and
// see what happens. It turns out it'll be simpler to sort edges
// and then add, kruskal's-style, rather than mantaining a queue.
//
// The first thing we can notice is that all edges of the same
// "type", that being, all flights between same-index cities
// or all portals between same-index planets will be added all
// at once. So, it looks like we can significantly optimize by
// treating all same-type edges as one, and somehow computing
// how many times they will need to be added.
//
// How do we calculate the number of additions? Take for example
// this setup with 2 planets and 4 cities per planet:
//
//   1,1           2,1
//    |             |
//   1,2           2,2
//     
//   1,3           2,3
//    |             |
//   1,4           2,4
//
// Say we can add a portal between planets 1 and 2. How many times
// at minimum do we add this edge?
//
// Here it's easy: both planets have the same "structure" of
// connected components, so we only need to add one portal per
// component. But what if the planets have different structure?
// I claim that all planets will *always* have identical structure.
//
// What if we're adding a flight instead of a portal? Consider:
//
//   1,1 ---- 2,1      3,1
//
//   1,2 ---- 2,2      3,2
//
// Here we're assuming that the portals are of identical structure,
// but I claim that this too will always happen. Anyway, we only
// need to add two edges, as there are only two "connected components"
// in the graph of the planets.
//
// This, if our mirror assumption holds, would be enough to solve the
// problem. Let's try to prove this:
//
// First, why must planets have the same structure? Let's try to prove
// by contradiction: Under what conditions would we *not* add a flight
// uniformly to all planets? We've actually seen this in an example
// before:
//
//   1,1 ---- 2,1      3,1
//    |                 |
//   1,2 ---- 2,2      3,2
//
// Here, we didn't need to add a flight on planet 2 because planets
// 1 and 2 formed a connected component, and so adding a flight on
// only planet 1 was sufficient. But now look: If we want to add
// a portal between planets 2 and 3, the "structure" is still actually
// the same; both planets have city 1 and 2 in the same connected
// component.
//
// The same logic can be applied to show that adding portals mantains
// connected component-ness across planets.

#include <algorithm>
#include <iostream>
#include <array>

using LL = long long;

// flights are "internal" and portals are "external"
std::array<int, 3> in[100000], out[100000];
// combine all edge types together and sort
std::array<int, 4> all[200000];

// DSU to store components formed by cities (inroot) as well
// as components formed by planets (outroot), and also their
// count of components
int inroot[100000], outroot[100000], incomps, outcomps;

int find(int *root, int i){
	if(root[i] < 0) return i;
	return root[i] = find(root, root[i]);
}

int main(){
	int n, m, p, q; std::cin >> n >> m >> p >> q;

	// input everything.. so messy
	for(int i=0; i<p; ++i) std::cin >> in[i][1] >> in[i][2] >> in[i][0], --in[i][1], --in[i][2];
	for(int i=0; i<q; ++i) std::cin >> out[i][1] >> out[i][2] >> out[i][0], --out[i][1], --out[i][2];

	for(int i=0; i<p; ++i)
		all[i][0] = in[i][0], all[i][1] = in[i][1], all[i][2] = in[i][2], all[i][3] = 1;
	for(int i=0; i<q; ++i)
		all[i+p][0] = out[i][0], all[i+p][1] = out[i][1], all[i+p][2] = out[i][2];

	// init DSU structures (store size in same array)
	for(int i=0; i<n; ++i) outroot[i] = -1;
	for(int i=0; i<m; ++i) inroot[i] = -1;
	outcomps = n, incomps = m;

	std::sort(all, all+p+q);

	// maximum saved - assume everything can be removed, and then add
	// back the cost of edges we use, multiplied by their occurance
	LL max = 0;

	for(int i=0; i<p+q; ++i){
		// edge is a flight
		if(all[i][3]){
			// like mentioned before we assume we use this flight
			max += (LL)all[i][0] * n;

			// check if these city types are already in the same
			// component, and if so, do nothing
			int a = find(inroot, all[i][2]), b = find(inroot, all[i][1]);
			if(a == b) continue;

			// occurances of this flight is precisely equal to
			// the number of components formed by planets
			max -= (LL)all[i][0] * outcomps;

			// update components
			if(a < b) inroot[a] += inroot[b], inroot[b] = a;
			else inroot[b] += inroot[a], inroot[a] = b;
			--incomps;
	
		// edge is a portal
		}else{
			// identical, but with the other variable set
			max += (LL)all[i][0] * m;

			int a = find(outroot, all[i][2]), b = find(outroot, all[i][1]);
			if(a == b) continue;

			
			max -= (LL)all[i][0] * incomps;
			if(a < b) outroot[a] += outroot[b], outroot[b] = a;
			else outroot[b] += outroot[a], outroot[a] = b;
			--outcomps;
		}
	}

	// it is really that easy
	std::cout << max << '\n';
}
