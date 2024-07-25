// Distinct Value Queries  -  https://cses.fi/problemset/task/1734
//
// process queries offline; notice that for each right endpoint,
// the set of queries on all left endpoints is monotonically
// decreasing or something bc of influence of values:
//
//   1 2 3 2 4
//   --+---+     <- only left endpoints in this region include
//                  the 2 in their distinct values
//
// so we can do this by range updating a segtree (no need for lazy
// prop as we only need point queries)
//
// (am tired pls ignore)

#include <iostream>
#include <vector>
#include <array>
#include <map>

// values, answer to queries, n
int a[200001], ans[200001], n;
std::vector<std::array<int, 2>> query[200001];

// segtree + operations

int tree[400001];

void add(int l, int r){  // always just an increment
	for(l += n, r += n; l < r; l >>= 1, r >>= 1){
		if(l&1) ++tree[l++];
		if(r&1) ++tree[--r];
	}
}

int get(int i){
	int res = 0;
	for(i += n; i; i >>= 1) res += tree[i];
	return res;
}

int main(){
	int q; std::cin >> n >> q;
	for(int i=0; i<n; ++i) std::cin >> a[i];

	for(int i=0; i<q; ++i){
		int a, b; std::cin >> a >> b, --a, --b;
		query[b].push_back({a, i});
	}

	// in our example of 1 2 3 2 4, the second 2 only increments
	// the range from the 3..2 seeing that previous elements were
	// already incremented by the other 2: so, we store last seen
	// position of each element and use for index
	std::map<int, int> last;

	for(int i=0; i<n; ++i){
		if(!last.count(a[i])) last[a[i]] = 0;
		add(last[a[i]], i+1), last[a[i]] = i+1;

		for(const auto &[l, x] : query[i]) ans[x] = get(l);
	}

	for(int i=0; i<q; ++i) std::cout << ans[i] << '\n';
}
