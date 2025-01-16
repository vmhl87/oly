#include <iostream>
#include <string>

using ll = long long;

ll a[2][2019];

int main(){
	std::string s; std::cin >> s;

	ll res = 0; a[0][0] = 1;
	int x = 0;

	for(char c : s){
		int b = c-'0';
		std::fill(a[x^1], a[x^1]+2019, 0);

		for(int i=0; i<2019; ++i)
			a[x^1][(i*10+b)%2019] += a[x][i];

		res += a[x^1][0];

		++a[x^1][0], x ^= 1;
	}

	std::cout << res << '\n';
}
