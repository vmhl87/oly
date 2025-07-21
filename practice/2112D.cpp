// URL: https://codeforces.com/problemset/problem/2112/D

#include <algorithm>
#include <iostream>
#include <bitset>
#include <vector>

const int N = 2e5;

std::vector<int> a[N];
std::bitset<N> c;

void color(int i, int p, bool x){
	c[i] = x;

	for(int j : a[i]) if(j != p)
		color(j, i, x^1);
}

void test(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i) a[i].clear();

	for(int i=1; i<n; ++i){
		int x, y; std::cin >> x >> y, --x, --y;
		a[x].push_back(y), a[y].push_back(x);
	}

	int f = -1;

	for(int i=0; i<n; ++i) if(a[i].size() == 2) f = i;

	if(f < 0){
		std::cout << "NO\n";
		return;
	}

	std::cout << "YES\n";

	int F = a[f][0];

	a[f].erase(std::find(a[f].begin(), a[f].end(), F));
	a[F].erase(std::find(a[F].begin(), a[F].end(), f));

	color(f, f, 0);
	color(F, F, 0);

	for(int i=0; i<n; ++i) if(c[i])
		for(int j : a[i]) std::cout << i+1 << ' ' << j+1 << '\n';

	std::cout << f+1 << ' ' << F+1 << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
