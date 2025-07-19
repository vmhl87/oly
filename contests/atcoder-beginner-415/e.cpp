#include <iostream>

using ll = long long;
const int N = 2e5;

ll a[N], p[N], b[N];
int h, w;

ll g(int x, int y) { return a[w*x + y]; }
void s(int x, int y, ll v) { a[w*x + y] = v; }

ll g2(int x, int y) { return b[w*x + y]; }
void s2(int x, int y, ll v) { b[w*x + y] = v; }

int main(){
	std::cin >> h >> w;

	for(int i=0; i<h; ++i)
		for(int j=0; j<w; ++j){
			ll x; std::cin >> x;
			s(i, j, x);
		}

	for(int i=0; i<w+h-1; ++i) std::cin >> p[i];

	s2(h-1, w-1, std::max(0ll, p[h+w-2] - g(h-1, w-1)));

	for(int i=h-1; i>=0; --i)
		for(int j=w-1; j>=0; --j){
			if(i == h-1 && j == w-1) continue;
			ll x1 = i < h-1 ? g2(i+1, j) : 1e18;
			ll x2 = j < w-1 ? g2(i, j+1) : 1e18;
			s2(i, j, std::max(0ll, std::min(x1, x2) + p[i+j] - g(i, j)));
		}

	std::cout << g2(0, 0) << '\n';

	/*
	b[h-1] = 0;
	for(int i=0; i<h-1; ++i) b[i] = 1e18;

	for(int i=w+h-2; i>0; --i){
		//std::cout << "x: "; for(int j=0; j<h; ++j) std::cout << b[j] << " \n"[j==h-1];

		// old cell coords: (i-j j)
		for(int j=std::max(0, i-w+1); j<=std::min(w-1, i); ++j){
			// if(i-j < 0 || i-j >= w) { b[j] = 1e18; continue; }
			b[j] = std::max(0ll, b[j] + p[i] - g(j, i-j));
		}

		//std::cout << "y: "; for(int j=0; j<h; ++j) std::cout << b[j] << " \n"[j==h-1];

		// new cell coords: (i-j-1 j)
		for(int j=std::max(0, i-w); j<=std::min(w-1, i-1); ++j){
			// if(i-j-1 < 0 || i-j-1 >= w) { c[j] = 1e18; continue; }
			if(j == h-1) c[j] = std::max(0ll, b[j]);
			else c[j] = std::max(0ll, std::min(b[j], b[j+1]));
		}

		for(int j=0; j<h; ++j) b[j] = c[j];

		//std::cout << "z: "; for(int j=0; j<h; ++j) std::cout << b[j] << " \n"[j==h-1];
	}

	std::cout << std::max(0ll, b[0]+p[0]-g(0,0)) << '\n';
	*/
}
