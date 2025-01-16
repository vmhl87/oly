#include <iostream>

using ll = long long;

void test(){
	ll a[6]; for(int i=0; i<6; ++i) std::cin >> a[i];
	ll res = a[0]*a[3] + a[2]*a[5] + a[4]*a[1] - a[1]*a[2] - a[3]*a[4] - a[5]*a[0];
	std::cout << (res > 0 ? "LEFT" : (res < 0 ? "RIGHT" : "TOUCH")) << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
