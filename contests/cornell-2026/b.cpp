#include <iostream>

int main(){
	int n; std::cin >> n;
	int min=0, max=0;

	while(n--){
		int a, b; std::cin >> a >> b;
		min += b, max += b+a;
	}

	std::cout << min << ' ' << max << '\n';
}
