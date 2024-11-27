#include <iostream>

int block[200002][2];

int main(){
	int n; std::cin >> n;

	int run = 0, p = 0;
	char last = '0';

	for(int i=0; i<n; ++i){
		char c; std::cin >> c;

		if(c != last && run){
			block[p][0] = last;
			block[p++][1] = run;
			run = 0;
		}

		last = c, ++run;
	}

	block[p][0] = last;
	block[p++][1] = run;

	int best = 0;

	for(int i=1; i<p-1; ++i) if(block[i][0] == '/' && block[i][1] == 1)
		if(block[i-1][0] == '1' && block[i+1][0] == '2')
			best = std::max(best, std::min(block[i-1][1], block[i+1][1]));

	std::cout << 1+best+best << '\n';
}
