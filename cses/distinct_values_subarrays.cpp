#include <iostream>
#include <map>

using ll = long long;

std::map<int, int> last;

int main(){
	int n; std::cin >> n;

	ll res = 0;
	int len = 0;

	for(int i=0; i<n; ++i){
		int x; std::cin >> x;
		len = std::min(len, i-last[x]), ++len;
		last[x] = i+1;
		res += len;
	}

	std::cout << res << '\n';
}
