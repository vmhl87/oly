#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using oset = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#include <iostream>

const int N = 2e5;

int a[N], l[N+1], r[N+1];

int main(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> a[i];

	{
		oset<int> s;

		for(int i=0; i<n; ++i){
			auto x = s.upper_bound(a[i]);
			if(x == s.end()) l[i+1] = l[i];
			else l[i+1] = l[i]+s.size()-s.order_of_key(*x);
			s.insert(a[i]);
		}
	};

	{
		oset<int> s;

		for(int i=0; i<n; ++i){
			auto x = s.upper_bound(a[n-i-1]);
			if(x == s.end()) r[i+1] = r[i];
			else r[i+1] = r[i]+s.size()-s.order_of_key(*x);
			s.insert(a[n-i-1]);
		}
	};

	// for(int i=0; i<=n; ++i) std::cout << l[i] << " \n"[i==n];
	// for(int i=0; i<=n; ++i) std::cout << r[i] << " \n"[i==n];

	int res = 1e9;

	for(int i=0; i<=n; ++i)
		res = std::min(res, l[i]+r[n-i]);

	std::cout << res << '\n';
}
