#include <iostream>

void test_case(){
	int n, k; std::cin >> n >> k, --k;
	int start = 0, step = 1, now = 1;

	while(1){
		int cycle = start;
		if(now && start + step < n)
			cycle = start + step;
		else start += step;
		if(cycle >= n) break;
		now = (1+(n-cycle-1)/step) & 1;
		step *= 2;
		if(k < 1+(n-cycle-1)/step){
			std::cout << cycle+k*step+1 << '\n';
			return;
		}else k -= 1+(n-cycle-1)/step;
	}
}

int main(){
	int t; std::cin >> t;
	while(t--) test_case();
}
