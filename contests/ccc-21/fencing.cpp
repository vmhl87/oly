#include <iostream>

int h[10001], w[10000];

int main(){
	int n; std::cin >> n;

	for(int i=0; i<=n; ++i) std::cin >> h[i];

	for(int i=0; i<n; ++i) std::cin >> w[i];

	int res = 0;
	for(int i=0; i<n; ++i) res += w[i] * (h[i] + h[i+1]);

	std::cout << res/2 << (res&1 ? ".5\n" : "\n");
}
