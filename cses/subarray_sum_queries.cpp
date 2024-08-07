#include <iostream>

using LL = long long;

// store for each segment the maximum sum of a subarray
//  - enclosed anywhere in the segment
//  - a prefix
//  - a suffix
//  - the entire segment

struct sector{
	LL in, left, right, all;
};

const int sz = 1<<18;
sector tree[sz*2];

void set(int i, int v){
	tree[i].all = v;
	tree[i].in = std::max(0LL, tree[i].all);
	tree[i].left = std::max(0LL, tree[i].all);
	tree[i].right = std::max(0LL, tree[i].all);
}

// merge segments
//  - all is trivial
//  - largest subarray entirely inside segment is either entirely
//    in the left segment, or entirely in the right one, or a combination
//    of a suffix of left and prefix of right
//  - best prefix is either a prefix of left or all of left + prefix of right
//  - suffix is similar

void prop(int i){
	tree[i].all = tree[i<<1].all + tree[i<<1|1].all;
	tree[i].in = std::max(tree[i<<1].in, tree[i<<1|1].in);
	tree[i].in = std::max(tree[i].in, tree[i<<1].right + tree[i<<1|1].left);
	tree[i].left = std::max(tree[i<<1].left, tree[i<<1].all + tree[i<<1|1].left);
	tree[i].right = std::max(tree[i<<1|1].right, tree[i<<1].right + tree[i<<1|1].all);
}

int main(){
	int n, m, v; std::cin >> n >> m;

	for(int i=0; i<n; ++i) std::cin >> v, set(i+sz, v);
	for(int i=sz-1; i; --i) prop(i);

	while(m--){
		int k, x; std::cin >> k >> x, k += sz-1, set(k, x);
		for(k /= 2; k; k /= 2) prop(k);
		std::cout << tree[1].in << '\n';
	}
}
