#include <algorithm>
#include <iostream>
#include <array>

struct P{
	char t;
	int x, y;
};

P a[(size_t) 2e5];

bool ortho[256], diag[256];

void test(){
	int n, m; std::cin >> n >> m;

	int k; std::cin >> k;

	for(int i=0; i<k; ++i)
		std::cin >> a[i].t >> a[i].x >> a[i].y;

	int res = 0;

	// collisions on column
	
	{
		std::sort(a, a+k, [] (P x, P y) {
			if(x.x == y.x) return x.y < y.y;
			return x.x < y.x;
		});

		char last = 0;
		int cv = -1;

		for(int i=0; i<k; ++i){
			if(cv != a[i].x) last = a[i].t, cv = a[i].x;
			else{
				res += ortho[last] + ortho[a[i].t];
				last = a[i].t;
			}
		}
	};

	// collisions on row
	
	{
		std::sort(a, a+k, [] (P x, P y) {
			if(x.y == y.y) return x.x < y.x;
			return x.y < y.y;
		});

		char last = 0;
		int cv = -1;

		for(int i=0; i<k; ++i){
			if(cv != a[i].y) last = a[i].t, cv = a[i].y;
			else{
				res += ortho[last] + ortho[a[i].t];
				last = a[i].t;
			}
		}
	};

	// collisions on +diag
	
	{
		std::sort(a, a+k,
			[] (P x, P y) {
				if(x.x+x.y == y.x+y.y) return x.x < y.x;
				return x.x+x.y < y.x+y.y;
		});


		char last = 0;
		int cv = -1;

		for(int i=0; i<k; ++i){
			if(cv != a[i].x+a[i].y)
				last = a[i].t, cv = a[i].x+a[i].y;
			else{
				res += diag[last] + diag[a[i].t];
				last = a[i].t;
			}
		}
	};

	// collisions on -diag
	
	{
		std::sort(a, a+k,
			[] (P x, P y) {
				if(x.x-x.y == y.x-y.y) return x.x < y.x;
				return x.x-x.y < y.x-y.y;
		});

		char last = 0;
		int cv = a[0].x-a[0].y-1;

		for(int i=0; i<k; ++i){
			if(cv != a[i].x-a[i].y)
				last = a[i].t, cv = a[i].x-a[i].y;
			else{
				res += diag[last] + diag[a[i].t];
				last = a[i].t;
			}
		}
	};

	std::cout << res << '\n';
}

/*

- - - R
- R - -
R - - Q
- - - -
- - - -
- - - B
- Q - -

*/

int main(){
	ortho['Q'] = 1;
	ortho['R'] = 1;
	diag['Q'] = 1;
	diag['B'] = 1;
	int t; std::cin >> t;
	while(t--) test();
}
