#include <iostream>
#include <vector>

using LL = long long;

void test_case(){
	LL n, on; std::cin >> n, on = n;

	std::vector<LL> pow;
	LL cur = 1;

	for(; n; n >>= 1, cur <<= 1)
		if(n & 1) pow.push_back(cur);

	if(pow.size() == 1){
		std::cout << 1 << '\n';
	}else{
		std::cout << pow.size() + 1 << '\n';

		for(auto x = pow.rbegin(); x != pow.rend(); ++x)
			std::cout << on - *x << ' ';
	}
	
	std::cout << on << '\n';
}

int main(){
	int t; std::cin >> t;

	while(t--) test_case();
}
