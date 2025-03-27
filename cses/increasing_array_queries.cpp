// https://cses.fi/problemset/task/2416/
//
// I didn't use a segtree, which I think is somewhat unusual.
//
// Visualizing the array as a height-graph sort of thing, the "make increasing"
// operation turned into something similar to leveling off the array, almost as
// if the height-graph were a basin in which water was being poured:
//
//                                   #
//                                   #     #
//                                   # #...#
//                                 # # # # #
//                                     <--->
//                                
//                                   #......
//                                   #.....#
//                                   # #...#
//                                 # # # # #
//                                   <----->
// 
// This stuck out to me as looking sort of like monstack: when "filling" these
// basins, we sort of draw lines moving horizontally to the right of each tower,
// until they hit another tower (or run off the side). Because this is the same
// as finding nearest largest neighbor to the right, monstack can do it.
//
// Each range query then also breaks down into a sequence of "basins", identified
// by the "upper hull" of all of the towers in the range, as illustrated:
//
//                                                #
//                                        #....   #
//                                    #...#....   #
//                            #       # # #.... # #
//                            #   #...# # #.... # # #
//                          # # # # # # # # # # # # # #
//                                <----------->
//
// This upper hull is the sequence of "prefix maximums" - indices such that there
// exist no values before them which are of larger value. (This is fairly trivially
// computed via monstack). Also, computing the "fill amount" of each basin is pretty
// easy: The "filled basin" becomes a rectangle, whose width is the width of the range,
// and height is the largest element in the range. Thus, we can compute the fill amt
// by subtracting the sum of all values in range from the area of the rectangle, which
// can be done with a prefix sum.
//
// In order to implement this process, we can compute the "next largest element" for
// each index. Then we can show that the upper hull will be identical to the sequence
//                  {start, next[start], next[next[start]], ...}.
//
// Unfortunately, this approach results in O(N) worst-case time complexity. Note that
// next[x] is always greater than x. Thus, we can construct the tree where each node
// x's parent is next[x]. Then, each upper hull will be an ascending path along this
// tree, which we need to find the sum of. This can be done with either binary lifting
// or euler tour.

#include <iostream>
#include <vector>

using ll = long long;
const int maxn = 2e5;

int next[18][maxn+1], x[maxn];

// p is pfx sum, c is cost
ll p[maxn+1], c[18][maxn+1];

// fill amt of a basin from [l, r)
ll cost(int l, int r){
	return (ll)x[l]*(r-l) - (p[r]-p[l]);
}

int main(){
	int n, q; std::cin >> n >> q;
	for(int i=0; i<n; ++i) std::cin >> x[i];

	// monstack
	
	std::vector<int> s;

	for(int i=0; i<n; ++i){
		while(s.size() && x[s.back()] < x[i])
			next[0][s.back()] = i, s.pop_back();

		s.push_back(i);
	}

	for(int i : s) next[0][i] = n;

	// binlift

	for(int i=0; i<n; ++i) p[i+1] = p[i] + x[i];
	
	for(int i=0; i<n; ++i) c[0][i] = cost(i, next[0][i]);

	next[0][n] = n, c[0][n] = 0;

	for(int i=1; i<18; ++i)
		for(int j=0; j<=n; ++j)
			next[i][j] = next[i-1][next[i-1][j]],
			c[i][j] = c[i-1][j] + c[i-1][next[i-1][j]];
	
	// answer queries

	while(q--){
		int a, b; std::cin >> a >> b, --a;

		ll res = 0;

		// ascend tree w/ binlift
		for(int i=17; i>=0; --i)
			if(next[i][a] < b) res += c[i][a], a = next[i][a];
		
		// clean up the end
		if(a != b) res += cost(a, b);

		std::cout << res << '\n';
	}
}
