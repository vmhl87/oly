#include <iostream>

void test_case(){
	int n; std::cin >> n;

	char t;
	int st[n];

	for(int i=0; i<n; ++i) std::cin >> t, st[i] = t - '0';

	if(n == 3 && st[0] * st[2] == 0){
		std::cout << 0 << '\n';
		return;
	}

	if(n > 3)
		for(int i : st) if(i == 0){
			std::cout << 0 << '\n';
			return;
		}

	int base = 0;

	for(int i : st) if(i > 1) base += i;

	int best = base + st[0]*10 + st[1];

	for(int i=0; i<n-1; ++i){
		int current = base;
		if(st[i] > 1) current -= st[i];
		if(st[i+1] > 1) current -= st[i+1];

		if(st[i]*10 + st[i+1] != 1) current += st[i]*10 + st[i+1];
		else if(current == 0) ++current;

		if(current < best) best = current;
	}

	std::cout << best << '\n';
}

int main(){
	int t; std::cin >> t;

	while(t--) test_case();
}
