#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
#define oset __gnu_pbds::tree<int, __gnu_pbds::null_type, std::less<int>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>

#include <iostream>
#include <cmath>

inline int bubble_sort(int n, int *p, int *r){
	int index[n];
	oset s;
	for(int i=n-1; i>=0; --i){
		auto x = s.lower_bound(p[i]);
		int dist = s.size();
		if(x != s.end()) dist = s.order_of_key(*x);
		// std::cout << p[i] << " shifted by " << dist << " : " << *s.lower_bound(p[i]) << '\n';
		index[p[i]-1] = i+dist;
		s.insert(p[i]);
	}
	// for(int idx : index) std::cout << idx << ' '; std::cout << '\n';
	// for(int i=0; i<n; ++i) std::cout << i << ' '; std::cout << '\n';
	// for(int i=0; i<n; ++i) std::cout << std::abs(index[i] - i) << ' '; std::cout << '\n';
	int swaps = 0;
	for(int i=0; i<n; ++i) swaps += std::abs(index[i] - i);
	return swaps;
}

int main(){
	int n; std::cin >> n;
	int p[n], r[n];
	for(int i=0; i<n; ++i)
		std::cin >> p[i], r[p[i]-1] = i;
	int s1 = bubble_sort(n, p, r);
	std::cout << s1 << '\n';
}

/*
8
7 8 2 6 5 1 3 4
        ---
7 8 2 6 1 5 3 4
      ---
7 8 2 1 6 5 3 4
    ---
7 8 1 2 6 5 3 4
*/
