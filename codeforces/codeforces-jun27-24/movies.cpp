#include <iostream>
#include <cmath>

void test_case(){
	int n; std::cin >> n;

	// wait the greedy is like actually not complicated lmao
	
	int a[n], b[n];

	for(int i=0; i<n; ++i) std::cin >> a[i];
	for(int i=0; i<n; ++i) std::cin >> b[i];

	int ta = 0, tb = 0, tc = 0, td = 0;

	for(int i=0; i<n; ++i){
		if(a[i] + b[i] == 2){
			++tc;
			continue;
		}
		if(a[i] + b[i] == -2){
			++td;
			continue;
		}

		if(b[i] > a[i]) tb += b[i];
		else ta += a[i];
	}

	int diff = std::abs(ta - tb);

	if(ta > tb) ta -= std::min(td, diff);
	else tb -= std::min(td, diff);

	td -= std::min(td, diff);

	ta -= td/2, tb -= td/2;

	if(td & 1) --ta;

	diff = std::abs(ta - tb);

	if(ta < tb) ta += std::min(tc, diff);
	else tb += std::min(tc, diff);

	tc -= std::min(tc, diff);

	ta += tc/2, tb += tc/2;

	std::cout << std::min(ta, tb) << '\n';
}

int main(){
	int t; std::cin >> t;

	while(t--) test_case();
}
