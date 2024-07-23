#include <algorithm>
#include <iostream>

int v[100];

int main(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> v[i];
	std::sort(v, v+n);

	int best = 2e9;

	// edge villages are infinite size so no point in processing
	for(int i=1; i<n-1; ++i){
		int current = v[i+1] - v[i-1];
		if(current < best) best = current;
	}

	// imagine using floating point
	std::cout << best/2 << '.' << (best&1 ? '5' : '0') << '\n';
}
