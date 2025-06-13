#include <iostream>
#include <array>
#include <set>

const int N = 2e5;

int a[N], p[N+1];

int sum(int l, int r){
	return p[r] - p[l];
}

void test(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i){
		char c; std::cin >> c;
		a[i] = c - '0';
	}

	std::set<std::array<int, 2>> s;
	s.insert({0, 0});

	for(int i=0; i<n; ++i)
		p[i+1] = p[i] + (a[i] ? 1 : -1),
			s.insert({-p[i+1], i+1});

	std::array<int, 3> best = {0, 0, 0};
	
	/*
	 0  1
	0 -1 0
	{0 0} {1 1} {0 2}
	-1, 0  -->  0 - (-1)
	*/

	for(int i=0; i<n; ++i){
		auto max = *s.begin();
		best = std::max(best, {-max[0]-p[i], i, max[1]});
		s.erase({-p[i], i});
	}

	for(int i=0; i<n; ++i) p[i+1] = p[i] + a[i];

	std::cout << sum(0, n) - sum(best[1], best[2])*2 + best[2]-best[1] << '\n';
	// std::cout << '[' << best[1] << ' ' << best[2] << "]\n";
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
