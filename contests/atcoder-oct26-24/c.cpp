#include <iostream>
#include <array>
#include <set>

using ll = long long;
ll n;

std::set<std::array<int, 2>> use;
void remove(int x, int y){
	if(x < 1 || x > n || y < 1 || y > n) return;
	use.insert({x, y});
}

int main(){
	int m; std::cin >> n >> m;
	while(m--){
		int a, b; std::cin >> a >> b;
		remove(a, b);
		remove(a+2, b+1);
		remove(a+1, b+2);
		remove(a-2, b+1);
		remove(a-1, b+2);
		remove(a+2, b-1);
		remove(a+1, b-2);
		remove(a-2, b-1);
		remove(a-1, b-2);
	}

	std::cout << (n*n - use.size()) << '\n';
}
