#include <iostream>

using ll = long long;

void test(){
	ll n, m; std::cin >> n >> m;
	ll res = n*(n+1) % m;
	if(res > 0 && res <= n) std::cout << "Bob\n";
	else std::cout << "Alice\n";
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
