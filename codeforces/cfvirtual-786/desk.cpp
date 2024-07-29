#include <ext/pb_ds/assoc_container.hpp> 
using namespace __gnu_pbds;
template<typename T>
using oset = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#include <iostream>

int main(){
	int n, m, q; std::cin >> n >> m >> q;

	oset<int> o;

	bool a[n][m];

	for(int i=0; i<n; ++i)
		for(int j=0; j<m; ++j){
			char c; std::cin >> c;
			a[i][j] = c=='*';
		}

	for(int i=0; i<n; ++i)
		for(int j=0; j<m; ++j)
			if(a[i][j]) o.insert(i+j*n);

	while(q--){
		int x, y; std::cin >> y >> x, --x, --y;

		if(a[y][x]){
			a[y][x] = 0;
			o.erase(y+x*n);
		}else{
			a[y][x] = 1;
			o.insert(y+x*n);
		}

		int l = -1, r = o.size()-1;

		while(l < r){
			int m = (l+r+1)/2;

			int at = *o.find_by_order(m);

			// m'th element, therefore there are
			// o.size()-m-1 elem bigger & at-m holes before

			if(o.size()-m-1 < at-m) r = m-1;
			else l = m;
		}

		std::cout << o.size()-l-1 << '\n';
	}
}
