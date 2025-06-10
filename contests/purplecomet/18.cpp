#include <iostream>

int a, t;

int valid(int i){
	int c = 0;
	bool v[4][4] = {};
	for(int j=0; j<16; ++j){
		if(i&(1<<j)){
			++c;
			v[j>>2][j&3] = 1;
		}
	}
	if(c != 8) return 0;
	for(int j=0; j<4; ++j){
		int x = 0;
		for(int k=0; k<4; ++k){
			if(v[j][k]) ++x;
		}
		if(x != 2) return 0;
	}
	for(int j=0; j<4; ++j){
		int x = 0;
		for(int k=0; k<4; ++k){
			if(v[k][j]) ++x;
		}
		if(x != 2) return 0;
	}
	{
		bool w = 1;
		for(int j=0; j<4; ++j){
			if(!v[j][j]) w = 0;
		}
		if(w) return 2;
	};
	{
		bool w = 1;
		for(int j=0; j<4; ++j){
			if(!v[3-j][j]) w = 0;
		}
		if(w) return 2;
	};
	return 1;
}

int main(){
	for(int i=0; i<1<<16; ++i){
		int v = valid(i);
		if(v == 0) continue;
		if(v == 2) ++a;
		++t;
	}
	std::cout << a << ' ' << t << '\n';
}
