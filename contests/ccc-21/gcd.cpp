// Math Homework
//
// With some observation we can show that for a combination
// of ranges which has a valid solution, a guaranteed valid
// array is one such that each element is the LCM of all ranges
// containing it.
//
// To keep track of LCM I used some frequency mapping over
// a sweep line loop - kind of overcomplicated
//
// Verifying whether or not the generated array violates
// constraints is simple with a little bit of segtree.

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <array>
#include <map>

int out[150001], tree[300002];
std::array<int, 3> all[150001];
std::map<int, int> comp[14];

int main(){
	int n, m; std::cin >> n >> m;

	std::vector<std::array<int, 2>> start, end;

	for(int i=0; i<m; ++i){
		int a, b, c; std::cin >> a >> b >> c, --a, --b;

		start.push_back({a, c});
		end.push_back({b, c});

		all[i][0] = a, all[i][1] = b, all[i][2] = c;
	}

	std::sort(start.begin(), start.end());
	std::sort(end.begin(), end.end());

	auto p1 = start.begin(), p2 = end.begin();
	int now = 1;

	// each frequency map stores the information for a single prime:
	// how many current ranges have what power of this prime?
	comp[2][0] = 1, comp[3][0] = 1, comp[5][0] = 1, comp[7][0] = 1,
		comp[11][0] = 1, comp[13][0];

	for(int i=0; i<n; ++i){
		// loop through starts
		while(p1 != start.end() && (*p1)[0] <= i){
			int x = (*p1)[1];
			std::map<int, int> curr;
			// extract prime powers
			for(int y=2; y<=x; ++y){
				while(x%y == 0){
					++curr[y];
					x /= y;
				}
			}
			// update index on the fly.. not very good
			for(const auto &[a, b] : curr){
				int top = (--comp[a].end())->first;
				++comp[a][b];
				for(; top < (--comp[a].end())->first; ++top)
					now *= a;
			}
			++p1;
		}

		out[i] = now;

		// loop through ends
		while(p2 != end.end() && (*p2)[0] <= i){
			int x = (*p2)[1];
			std::map<int, int> curr;
			for(int y=2; y<=x; ++y){
				while(x%y == 0){
					++curr[y];
					x /= y;
				}
			}
			for(const auto &[a, b] : curr){
				int top = (--comp[a].end())->first;
				--comp[a][b];
				if(!comp[a][b]) comp[a].erase(b);
				for(int low = (--comp[a].end())->first; low < top; ++low)
					now /= a;
			}
			++p2;
		}
	}

	// segtree was unironically the easy part
	for(int i=0; i<n; ++i) tree[i+n] = out[i];
	for(int i=n-1; i; --i) tree[i] = std::gcd(tree[i<<1], tree[i<<1|1]);

	for(int i=0; i<m; ++i){
		int l = all[i][0], r = all[i][1]+1, res = 0;
		
		for(l += n, r += n; l < r; l >>= 1, r >>= 1){
			if(l&1) res = std::gcd(res, tree[l++]);
			if(r&1) res = std::gcd(res, tree[--r]);
		}

		if(res != all[i][2]){
			std::cout << "Impossible\n";
			return 0;
		}
	}

	for(int i=0; i<n; ++i) std::cout << out[i] << " \n"[i==n-1];
}
