#include <iostream>

int main(){
	int a, b; std::cin >> a >> b;
	int best = 0, run = 0;

	while(a--){
		bool valid = 1;

		for(int i=0; i<b; ++i){
			int x; std::cin >> x;
			if(x != 0) valid = 0;
		}

		if(valid){
			++run;
			best = std::max(best, run);
		}else run = 0;
	}

	std::cout << best << '\n';
}
