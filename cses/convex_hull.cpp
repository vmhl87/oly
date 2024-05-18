// Convex Hull  -  https://cses.fi/problemset/task/2195/
// We sort the points on x, and then apply a semi-dp-like approach:
// by iterating left to right on the points, we can keep track of the
// current convex hull at each step, and each time we add a new point
// to the hull, we essentially just have to add that point to the end
// of the convex hull, and if this results in any concave sections,
// we can simply replace any pair of adjacent segments resulting in
// a concavity with a single segment.

#include <algorithm>
#include <iostream>
#include <array>
#include <stack>

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int n; std::cin >> n;
	
	// because of the need to retrieve the path later on and print it,
	// rather than store the 'current convex hull' as an explicit stack
	// or list of vertices, we can instead inside the point array itself
	// store for each point the index of the previous point on its hull.
	// we store two indexes for the top and bottom sections of the hull.
	std::array<int, 4> a[n];
	for(int i=0; i<n; ++i)
		std::cin >> a[i][0] >> a[i][1];

	// sort first on x, and then on y - this helps with organization. We
	// can additionally guarantee that the first and last points must be
	// on the hull no matter what, and this simplifies the computation.
	std::sort(a, a+n);

	// determine if the segment [i, j] is steeper than the segment [j, k]
	auto steeper = [&a](int i, int j, int k){
		return (long long)(a[i][1] - a[j][1])*(long long)(a[j][0] - a[k][0]) >
			(long long)(a[j][1] - a[k][1])*(long long)(a[i][0] - a[j][0]);
	};

	// len = length of virtual stack, i.e. list of vertex indices of the
	// current top hull (we use two passes, one to construct the top hull,
	// the other to construct the bottom hull)
	// top = top of virtual stack
	int len = 1, top = 0;

	// iterate forward and update top hull
	for(int i=1; i<n; ++i){
		// if there are two or more segments in the hull, check if the
		// newly added segment (current index i to top of stack) makes
		// a concavity, and if so, pop that index off of the stack
		while(len > 1 && steeper(i, top, a[top][2]))
			--len, top = a[top][2];
		// push current index to stack
		++len, a[i][2] = top, top = i;
	}

	// store total length of top hull, and reset in order to build the
	// bottom hull - we traverse right to left so that we can reuse the
	// steeper() function rather than make a shallower() function
	int total = len;
	len = 1, top = n-1;

	// identical to top hull, except we store back indexes in position
	// 3 instead of 2
	for(int i=n-2; i>=0; --i){
		while(len > 1 && steeper(i, top, a[top][3]))
			--len, top = a[top][3];
		++len, a[i][3] = top, top = i;
	}

	// print out length of total hull - subtract 2 because first and
	// last elements are counted twice
	std::cout << total + len - 2 << '\n';

	int p = 0;

	// traverse forward using the top hull
	while(p != n-1)
		std::cout << a[p][0] << ' ' << a[p][1] << '\n', p = a[p][3];

	// then traverse backward using the bottom hull
	while(p != 0)
		std::cout << a[p][0] << ' ' << a[p][1] << '\n', p = a[p][2];
}
