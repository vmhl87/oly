#include <iostream>

void test_case(){
	int n, k; std::cin >> n >> k;

	--k, --n;

	if(n % k == 0) n /= k;
	else n = (n/k) + 1;

	std::cout << n << '\n';
}

int main(){
	int n; std::cin >> n;

	while(n--) test_case();
}
