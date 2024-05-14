// Salary Queries  -  https://cses.fi/problemset/task/1144/
// Rather than bashing this with ordered_set, this problem is doable
// with a datastructure that supports efficient point updates and
// range sums, which segtree or BIT can do.
// Essentially, if we sort every possible salary that an employee can
// have and store them at the leaves of some sort of tree, then we
// can perform updates and ranges on this segment tree to find the
// results of each query.
// My implementation uses a std::map to compress salaries -> leaves,
// so it ends up being about the same speed as the ordered_set.

#include <iostream>
#include <array>
#include <map>

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int n, q; std::cin >> n >> q;

	// all is initially used to count the number of workers with
	// each salary, and then is used later to map salary -> leaf
	std::map<int, int> all;
	// *sal stores the salary of each worker to update correctly
	int sal[n];

	for(int i=0; i<n; ++i){
		std::cin >> sal[i];
		++all[sal[i]];
	}

	// we need to look through every query before processing them
	// because our segtree implementation needs to know all of the
	// possible salaries that an employee could have before creation
	std::array<int, 3> query[q];
	for(int i=0; i<q; ++i){
		char c;
		std::cin >> c >> query[i][1] >> query[i][2];
		query[i][0] = c;

		// we use the std::map to sort and store all of the possible
		// salaries, so if this salary isn't in the map yet, we need
		// to put it there with value 0 (no workers with this salary)
		if(c == '!' && !all.count(query[i][2]))
			all[query[i][2]] = 0;
	}

	// create the segtree!
	int s = all.size(), tree[s<<1], c = 0;
	for(auto &a : all){
		// for all salaries in the map, fill the corresponding leaf
		// of the segtree with the count of workers
		tree[s+c] = a.second;
		// and then modify to map salary -> leaf index
		a.second = c++;
	}

	// fill internal nodes (this segtree just counts number of
	// workers in each node's subtree)
	for(int i=s-1; i>0; --i) tree[i] = tree[i<<1] + tree[i<<1|1];

	// iterate over queries
	for(const auto &a : query){
		if(a[0] == '!'){
			// if this is a 'set' query, we first need to decrease
			// the worker count at the old salary, and then increase
			// at the new salary:
			//     a[1] corresponds to the 1-indexed worker, so we
			//       subtract 1 to get the proper index
			//     then we query sal[] to get the old salary, and
			//       use the all<> map to get the leaf index
			//     finally we need to shift the leaf by s because
			//       we are using bottom up segtree
			int v = s+all[sal[a[1]-1]];
			// update segtree (decrement all nodes in the path from
			// root to leaf)
			while(v) --tree[v], v >>= 1;
			// repeat for the new salary, and increment instead
			v = s+all[a[2]];
			while(v) ++tree[v], v >>= 1;

			// update salary array
			sal[a[1]-1] = a[2];
		}else{
			// in a 'range' query, we need to find the leaves of the
			// tree which correspond to the bounds of the range.
			// My segtree range implementation uses an inclusive left
			// bound and exclusive right bound, so we increment a[2]
			// by 1 when searching.
			auto x = all.lower_bound(a[1]),
				 y = all.lower_bound(a[2]+1);

			// lower_bound gives us a pointer to all<>, which we need
			// to convert to a leaf index - however, if the pointer
			// points to the end of the map, we need to find manually.
			int l, r;

			if(x == all.end()) l = s;
			else l = x->second;
			if(y == all.end()) r = s;
			else r = y->second;

			// shift by s because of internal nodes (BUS)
			l += s, r += s;

			int ret = 0;
			// standardish segtree range find
			while(l < r){
				if(l&1) ret += tree[l++];
				if(r&1) ret += tree[--r];
				l >>= 1, r >>= 1;
			}

			std::cout << ret << '\n';
		}
	}
}
