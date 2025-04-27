#include <algorithm>
#include <tgmath.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <array>

const int N = 2e5;
using ll = long long;
using ld = long double;

std::array<ll, 2> a[N];

struct _slope { ll dy, dx; };

_slope get_slope(int i, int j){
	return { a[i][1]-a[j][1], a[i][0]-a[j][0] };
}

_slope slope(ll dy, ll dx){
	return { dy, dx };
}

int comp(_slope a, _slope b){
	ll diff = a.dy*b.dx - b.dy*a.dx;
	return diff == 0 ? 0 : (diff > 0 ? 1 : -1);
}

ll x, y, z;

ld dist(int i){
	//std::cout << "testing against " << a[i][0] << ' ' << a[i][1] << '\n';
	//ld A = x, B = y, C = (ll)z + (ll)x*(ld)a[i][0] + (ll)y*(ld)a[i][1];
	//return std::abs(C/(A + B*(B/A))) * sqrtl(1 + (B/A) * (B/A));
	return std::abs((ld)x*(ld)a[i][0] + (ld)y*(ld)a[i][1] + (ld)z) /
		sqrtl((ld)x*(ld)x + (ld)y*(ld)y);
}

int main(){
	int n, q; std::cin >> n >> q;

	for(int i=0; i<n; ++i)
		for(int j=0; j<2; ++j)
			std::cin >> a[i][j];

	std::sort(a, a+n);

	std::vector<int> upper, lower;

	for(int i=0; i<n; ++i){
		while(lower.size() > 1 && comp(
					get_slope(i, upper.back()),
					get_slope(i, upper[upper.size()-2])
				) == 1)
			upper.pop_back();
		upper.push_back(i);
	}

	for(int i=0; i<n; ++i){
		while(lower.size() > 1 && comp(
					get_slope(i, lower.back()),
					get_slope(i, lower[lower.size()-2])
				) == -1)
			lower.pop_back();
		lower.push_back(i);
	}
	
	while(q--){
		std::cin >> x >> y >> z;
		_slope target = slope(-x, y);

		ld res = 0;

		{
			int i = 0;

			for(int s=1<<20; s; s/=2)
				if(i+s < upper.size() && comp(
							get_slope(upper[i+s], upper[i+s-1]),
							target) > 0)
					i += s;

			res = std::max(res, dist(i));
		};

		{
			int i = 0;

			for(int s=1<<20; s; s/=2)
				if(i+s < lower.size() && comp(
							get_slope(lower[i+s], lower[i+s-1]),
							target) < 0)
					i += s;

			res = std::max(res, dist(i));
		};

		std::cout << std::fixed << std::setprecision(10) << res << '\n';
	}
}
