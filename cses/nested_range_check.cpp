#include <algorithm>
#include <iostream>
#include <array>

std::array<int, 2> ranges[200000];
int tree[400000], tree_order[200000], tree_index[200000],
	walk_order[200000], ans[200000], n;

bool by_endpoint(int a, int b){
	if(ranges[a][1] == ranges[b][1]) return ranges[a][0] > ranges[b][0];
	return ranges[a][1] < ranges[b][1];
}

bool by_startpoint(int a, int b){
	if(ranges[a][0] == ranges[b][0]) return ranges[a][1] > ranges[b][1];
	return ranges[a][0] < ranges[b][0];
}

int get(int i){
	int ret = 0;
	for(i += n; i; i >>= 1) ret += tree[i];
	return ret;
}

void add(int l, int r){
	for(l += n, r += n; l < r; l >>= 1, r >>= 1){
		if(l&1) ++tree[l++];
		if(r&1) ++tree[--r];
	}
}

int main(){
	std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> ranges[i][0] >> ranges[i][1];
	/* pass 1 */
	for(int i=0; i<n; ++i) tree_order[i] = i, walk_order[i] = i;
	std::sort(tree_order, tree_order+n, by_endpoint);
	for(int i=0; i<n; ++i) tree_index[tree_order[i]] = i;
	std::sort(walk_order, walk_order+n, by_startpoint);
	for(int i=0; i<n; ++i){
		int l = 0, r = n;
		while(l < r){
			int m = (l+r)/2;
			if(ranges[tree_order[m]][1] < ranges[walk_order[i]][1])
				l = m+1;
			else r = m;
		}
		add(l, n);
		// add on range 0..ranges[walk_order[i]][1]
		ans[walk_order[i]] = -get(tree_index[walk_order[i]]);
	}
	for(int i=0; i<n; ++i)
		ans[i] += get(tree_index[i]);
	for(int i=0; i<n; ++i) std::cout << (ans[i]>0) << " \n"[i==n-1];
	/* pass 2 */
	for(int i=0; i<n; ++i) tree_order[i] = i, walk_order[i] = i;
	std::sort(tree_order, tree_order+n, by_startpoint);
	for(int i=0; i<n; ++i) tree_index[tree_order[i]] = i;
	std::sort(walk_order, walk_order+n, by_endpoint);
	for(int i=0; i<n; ++i){
		int l = 0, r = n;
		while(l < r){
			int m = (l+r)/2;
			if(ranges[tree_order[m]][0] < ranges[walk_order[i]][0])
				l = m+1;
			else r = m;
		}
		add(l, n);
		// add on range 0..ranges[walk_order[i]][1]
		ans[walk_order[i]] = -get(tree_index[walk_order[i]]);
	}
	for(int i=0; i<n; ++i)
		ans[i] += get(tree_index[i]);
	for(int i=0; i<n; ++i) std::cout << (ans[i]>0) << " \n"[i==n-1];
}
