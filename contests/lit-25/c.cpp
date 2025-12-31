#include <iostream>

using ll = long long;

void test(){
	int n; std::cin >> n;

	ll res = n;

	for(int i=1; i<=n; ++i){
		int p2 = __builtin_ctz(i);
		res += 2 * ((i-1)/(1<<p2));
	}

	std::cout << res << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
