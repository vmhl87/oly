#include <iostream>
#include <array>

using ll = long long;
const int N = 3e5;

int a[N][3];

int sqr(ll a, ll b){
	ll r = a*a + b*b;
	ll res = 0;
	for(ll x=1<<21; x; x/=2)
		if((res+x)*(res+x) <= r)
			res += x;
	return (int) res;
}

std::array<int, 4> l[2][N];
int ct[2];

int X, Y, v, res;

int cm(int a, int b){
	return std::abs(X-a) + std::abs(Y-b) + sqr(a, b);
}

void add(int x, int y){
	ct[v^1] = 0;
	res = 1e9;

	for(int i=0; i<ct[v]; ++i){
		const auto &[a, b, c, d] = l[v][i];
		if(x < a && x > c && y < b && y > d){
			l[v^1][ct[v^1]++] = {a, b, x, y};
			l[v^1][ct[v^1]++] = {x, y, c, d};
		}else if(a > x && b > y){
			l[v^1][ct[v^1]++] = {a, b, std::max(c, x), std::max(d, y)};
		}else if(c < x && d < y){
			l[v^1][ct[v^1]++] = {std::min(a, x), std::min(b, y), c, d};
		}
	}

	v ^= 1;

	for(int i=0; i<ct[v]; ++i){
		const auto &[a, b, c, d] = l[v][i];
		res = std::min(res,
				cm(
					std::max(c, std::min(a, X)),
					std::max(d, std::min(b, Y))
				)
			);
	}
}

int main(){
	int n, t; std::cin >> n >> t;
	std::cin >> X >> Y;

	for(int i=0; i<n; ++i)
		for(int j=0; j<3; ++j)
			std::cin >> a[i][j];
	
	l[0][ct[0]++] = {(int)2e6, (int)2e6, 0, 0};
	res = sqr(X, Y);

	for(int i=0, p=0; i<t; ++i){
		while(p < n && a[p][0] <= i)
			add(a[p][1], a[p][2]), ++p;
		//for(int j=0; j<ct[v]; ++j)
			//for(int k=0; k<4; ++k)
				//std::cout << l[v][j][k] << " \n"[k==3];
		std::cout << res << '\n';
	}
}
