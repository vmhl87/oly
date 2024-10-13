#include <iostream>

using ll = long long;

int b[200000];

void test(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> b[i];

	ll delta = 0, sum = b[n-1], ct = 1;
	
	for(int i=n-2; i>=0; --i){
		if(b[i] > sum/ct){
			delta += b[i] - sum/ct;
			b[i] = sum/ct;
		}else{
			ll part = sum/ct - b[i];
			b[i] += std::min(part, delta);
			delta -= std::min(part, delta);
		}

		sum += b[i], ++ct;
	}

	std::cout << (delta ? "No" : "Yes") << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
