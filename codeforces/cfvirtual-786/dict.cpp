#include <iostream>

int main(){
	int t; std::cin >> t;

	while(t--){
		char a, b; std::cin >> a >> b;

		int res = 25 * (a - 'a');

		if(b > a) --b;

		res += b - 'a' + 1;

		std::cout << res << '\n';
	}
}
