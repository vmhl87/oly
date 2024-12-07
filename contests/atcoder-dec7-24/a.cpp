#include <iostream>

int main(){
	int r = 0, l = 0;

	int n; std::cin >> n;

	while(n--){
		int t, v; std::cin >> t >> v;

		r = std::max(0, r - (t - l));
		r += v, l = t;
	}

	std::cout << r << '\n';
}
