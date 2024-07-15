#include <iostream>

void test_case(){
	int n; std::cin >> n;

	int delta = 0, run = 0, last = 'x';

	while(n--){
		char t; std::cin >> t;

		if(t == '1') ++delta, run = 0;
		else{
			if(last == '0') ++run;
			else --delta, run = 0;
		}

		last = t;
	}

	std::cout << (delta > 0 ? "Yes\n" : "No\n");
}

int main(){
	int t; std::cin >> t;

	while(t--) test_case();
}
