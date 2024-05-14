/*
7 10 4 8 5 3 1 6 2 9
7 4 8 10 5 3 1 6 2 9 (2)
4 7 8 10 5 3 1 6 2 9 (1)
         9 5 3 1 6 2 (5)
		 9 6 5 3 1 2 (3)
		 9 6 5 3 2 1 (1)

     4 8 5 3 1 6 2 9
	 9 4 8 5 3 1 6 2 (7)
	 9 8 4 5 3 1 6 2 (1)
	 9 8 6 4 5 3 1 2 (4)
	 9 8 6 5 4 3 1 2 (1)
	 9 8 6 5 4 3 2 1 (1) -> 14
*/

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using oset = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#include <iostream>

int main(){
	int n; std::cin >> n;
	int max = 0, v[n];
	for(int i=0; i<n; ++i)
		std::cin >> v[i], max = (v[i] > max ? v[i] : max);
	int mi;
	for(int i=0; i<n; ++i) if(v[i] == max) mi = i;
	long long ret = 0;
	oset<int> ls, rs;
	int dist[n];
	for(int i=mi-1; i>=0; --i){
		auto x = ls.lower_bound(v[i]);
		if(x == ls.end()) dist[i] = ls.size();
		else dist[i] = ls.order_of_key(*x);
		ls.insert(v[i]);
	}
	for(int i=mi+1; i<n; ++i){
		auto x = rs.lower_bound(v[i]);
		if(x == rs.end()) dist[i] = rs.size();
		else dist[i] = rs.order_of_key(*x);
		rs.insert(v[i]);
	}
	for(int i=0; i<mi; ++i)
		ret += i + dist[i] - ls.order_of_key(v[i]);
	for(int i=n-1; i>mi; --i)
		ret += n-1 - rs.order_of_key(v[i]) - i + dist[i];
	std::cout << ret << '\n';
}
