// Salary Queries  -  https://cses.fi/problemset/task/1144/
// We basically just cheese this with ordered set

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using oset = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#include <iostream>
#include <array>

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int n, q; std::cin >> n >> q;

	// each element of the ordered set is of the form {salary, index} so that
	// we can efficiently update salaries but also search primarily on salary
	oset<std::array<int, 2>> s;
	int sal[n];

	for(int i=0; i<n; ++i){
		std::cin >> sal[i];
		s.insert({sal[i], i});
	}

	for(int i=0; i<q; ++i){
		char c; int a, b;
		std::cin >> c >> a >> b;

		if(c == '?'){
			// find the bounds of the range with binary search
			auto x = s.lower_bound({a, -1}),
				 y = s.lower_bound({b+1, -1});

			// compute indices
			int p1, p2;
			if(x == s.end()) p1 = s.size();
			else p1 = s.order_of_key(*x);
			if(y == s.end()) p2 = s.size();
			else p2 = s.order_of_key(*y);

			// because the right endpoint is non-inclusive
			// we can just subtract
			std::cout << p2 - p1 << '\n';
		}else{
			// a is originally 1-indexed
			--a;
			
			// update salary by erasing and re-inserting
			s.erase({sal[a], a});
			s.insert({b, a});
			sal[a] = b;
		}
	}
}
