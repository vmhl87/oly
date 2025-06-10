#include <iostream>

bool works(int i){
	bool a[4][4] = {};
	for(int j=0; j<16; ++j){
		if(i&(1<<j)) a[j/4][j%4] = 1;
	}
	int sum = 0;
	if(a[0][0]) ++sum;
	if(a[0][1]) ++sum;
	if(a[1][0]) ++sum;
	if(a[1][1]) ++sum;

	for(int x=0; x<3; ++x)
		for(int y=0; y<3; ++y){
			int s = 0;
			for(int xx=0; xx<2; ++xx)
				for(int yy=0; yy<2; ++yy)
					if(a[xx+x][yy+y]) ++s;
			if(s != sum) return false;
		}

	return true;
}

int main(){
	int res = 0;
	for(int i=0; i<1<<16; ++i){
		if(works(i)) ++res;
	}
	std::cout << res << '\n';
}
