#include <algorithm>
#include <iostream>
#include <array>

std::array<int, 2> patch[200000];
int en[200000];

int main(){
	int n, m, k; std::cin >> k >> m >> n;

	for(int i=0; i<k; ++i) std::cin >> patch[i][0] >> patch[i][1];
	std::sort(patch, patch+k);

	for(int i=0; i<m; ++i) std::cin >> en[i];
	std::ort(en, en+m);

	// now do "two pointer" and go over all segments bounded by nhoj
}
