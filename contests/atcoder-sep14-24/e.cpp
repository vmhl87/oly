#include <iostream>
#include <map>

using ll = long long;

int main(){
	int n; std::cin >> n;

	std::map<int, int> last;

	ll total = 0, now = 0;

	for(int i=0; i<n; ++i){
		int x; std::cin >> x;
		now += i+1 - last[x];
		last[x] = i+1;
		total += now;
	}

	std::cout << total << '\n';
}
