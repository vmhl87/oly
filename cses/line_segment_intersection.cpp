#include <iostream>

using ll = long long;

ll a[8];

ll cycle(int i, int j, int k){
	ll res =
		a[i*2]*a[j*2+1] + a[j*2]*a[k*2+1] + a[k*2]*a[i*2+1] -
		a[i*2+1]*a[j*2] - a[j*2+1]*a[k*2] - a[k*2+1]*a[i*2];
	if(res > 0) return 1;
	if(res < 0) return -1;
	return 0;
}

void test(){
	for(int i=0; i<8; ++i) std::cin >> a[i];

	ll c[4] = {
		cycle(0, 1, 2), cycle(0, 1, 3),
		cycle(2, 3, 0), cycle(2, 3, 1)
	};

	if(c[0] == 0 && c[1] == 0 && c[2] == 0 && c[3] == 0){
		if(std::max(a[0], a[2]) >= std::min(a[4], a[6]) &&
		   std::max(a[4], a[6]) >= std::min(a[0], a[2]) &&
		   std::max(a[1], a[3]) >= std::min(a[5], a[7]) &&
		   std::max(a[5], a[7]) >= std::min(a[1], a[3]))
			std::cout << "YES\n";
		else std::cout << "NO\n";
	}else{
		if(c[0] == c[1] || c[2] == c[3]) std::cout << "NO\n";
		else std::cout << "YES\n";
	}
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
