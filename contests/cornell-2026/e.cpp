#include <iostream>

int main(){
	int n, m; std::cin >> n >> m;

	if(n < 2){
		std::cout << 0 << '\n';

		for(int i=0; i<n; ++i){
			for(int j=0; j<m; ++j){
				std::cout << '.';
			}

			std::cout << '\n';
		}

		return 0;
	}

	if(n == 2){
		int k = 0, p = m, f=0, block = 3;

		bool b[40] = {};

		while(p >= block){
			if(block == 3){
				b[f] = 1;
				b[f+1] = 1;
				b[f+2] = 0;
			}else{
				b[f] = 1;
				b[f+1] = 1;
			}

			++k; p -= block, f += block;
			block = 5-block;
		}

		std::cout << k << '\n';

		for(int i=0; i<n; ++i){
			for(int j=0; j<m; ++j){
				std::cout << (b[j] ? 'x' : '.');
			}

			std::cout << '\n';
		}
		
		return 0;
	}

	if(n == 3){
		int k = m/2;
		std::cout << k << '\n';

		for(int i=0; i<m; ++i)
			std::cout << (((i/2)&1) == 0 && i < k*2 ? 'x' : '.');

		std::cout << '\n';

		for(int i=0; i<m; ++i)
			std::cout << (i < k*2 ? 'x' : '.');

		std::cout << '\n';

		for(int i=0; i<m; ++i)
			std::cout << (((i/2)&1) == 1 && i < k*2 ? 'x' : '.');

		std::cout << '\n';
	}

	if(n > 3){
		bool out[50][50];
		int k = 0;

		auto fill = [&] (int i, int j){
			out[i][j] = 1;
			out[i+1][j] = 1;
			out[i][j+1] = 1;
			out[i+1][j+1] = 1;
		};

		for(int i=0; i<n/2; ++i){
			int w = m - (i&1), p = (i&1), block = 3;

			while(w >= block){
				fill(i*2, p);
				w -= block;
				p += block;
				block = 5-block;
			}
		}

		std::cout << k << '\n';

		for(int i=0; i<n; ++i){
			for(int j=0; j<m; ++j)
				std::cout << (out[i][j] ? 'x' : '.');
			std::cout << '\n';
		}
	}
}
