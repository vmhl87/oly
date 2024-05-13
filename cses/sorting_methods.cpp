#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
#define oset __gnu_pbds::tree<int, __gnu_pbds::null_type, std::less<int>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>

#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

inline long long bubble_sort(int n, int *p){
	int index[n];
	oset s;
	for(int i=n-1; i>=0; --i){
		auto x = s.lower_bound(p[i]);
		int dist = s.size();
		if(x != s.end()) dist = s.order_of_key(*x);
		index[p[i]-1] = i+dist;
		s.insert(p[i]);
	}
	long long swaps = 0;
	for(int i=0; i<n; ++i) swaps += std::abs(index[i] - i);
	return swaps;
}

inline int swap_sort(int n, int *p){
	int ret = n-1;
	for(int i=0; i<n; ++i) if(p[i] == i+1) --ret;
	return ret;
}

inline int move_sort(int n, int *p){
	std::vector<int> lis;
	for(int i=0; i<n; ++i){
		auto x = lower_bound(lis.begin(), lis.end(), p[i]);
		if(x == lis.end()) lis.push_back(p[i]);
		else lis[x - lis.begin()] = p[i];
	}
	return n - lis.size();
}

inline int front_sort(int n, int *p){
	int tr = n, ret = n;
	for(int i=n-1; i>=0; --i) if(p[i] == tr) --tr, --ret;
	return ret;
}

int main(){
	int n; std::cin >> n;
	int p[n];
	for(int i=0; i<n; ++i) std::cin >> p[i];
	long long s1 = bubble_sort(n, p);
	int s2 = swap_sort(n, p),
		s3 = move_sort(n, p),
		s4 = front_sort(n, p);
	std::cout << s1 << ' ' << s2 << ' ' << s3 << ' ' << s4 << '\n';
}

/*

1 2 3 4 5 6 7 8
7 8 2 6 5 1 3 4
  ---
7 2 8 6 5 1 3 4
    ---------
7 2 3 6 5 1 8 4
      -----
7 2 3 1 5 6 8 4
            ---
7 2 3 1 5 6 4 8
-------------
4 2 3 1 5 6 7 8
-------
1 2 3 4 5 6 7 8

1 2 3 4 5 6 7 8
7 8 2 6 5 1 3 4
-----------
1 8 2 6 5 7 3 4
  ---
1 2 8 6 5 7 3 4
    ---------
1 2 3 6 5 7 8 4
      ---------
1 2 3 4 5 7 8 6
          -----
1 2 3 4 5 6 8 7
            ---
1 2 3 4 5 6 7 8

#

*/
