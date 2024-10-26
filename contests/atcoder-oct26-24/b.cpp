#include <iostream>

bool use[8][8];

int main(){
	for(int i=0; i<8; ++i){
		for(int j=0; j<8; ++j){
			char c; std::cin >> c;
			if(c == '#'){
				for(int a=0; a<8; ++a)
					use[a][j] = 1,
						use[i][a] = 1;
			}
		}
	}

	int res = 0;
	for(int i=0; i<8; ++i)
		for(int j=0; j<8; ++j)
			if(!use[i][j]) ++res;

	std::cout << res << '\n';
}
