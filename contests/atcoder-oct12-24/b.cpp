#include <iostream>
#include <iomanip>
#include <cmath>

using ll = long long;

int main(){
	int n; std::cin >> n;
	ll x = 0, y = 0;
	double cost = 0;

	for(int i=0; i<n; ++i){
		ll a, b; std::cin >> a >> b;
		cost += sqrt((a-x)*(a-x) + (b-y)*(b-y));
		x = a, y = b;
	}

	cost += sqrt(x*x + y*y);

	std::cout << std::setprecision(20) << cost << '\n';
}
