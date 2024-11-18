#include <iostream>

int wb[1000000], zb[1000000];

int main(){
	int n, k; std::cin >> n >> k;

	int *wp = wb, *zp = zb, sign = 0, run = 0;
	bool wf = 0;

	for(int i=0; i<n; ++i){
		char c; std::cin >> c;

		if(c == sign) ++run;
		else if(run){
			if(sign == '0'){
				*(zp++) = run;
			}else{
				*(wp++) = run;
			}
			run = 1;
		}else wf = c == '1', run = 1;

		sign = c;
	}

	if(sign == '0'){
		*(zp++) = run;
	}else{
		*(wp++) = run;
	}

	int *zpp = zb, *wpp = wb;

	if(wf){
		for(int i=0; i<*wpp; ++i) std::cout << 1;
		++wpp, --k;
	}

	for(int i=1; i<k; ++i){
		if(zpp != zp){
			for(int i=0; i<*zpp; ++i) std::cout << 0;
			++zpp;
		}
		if(wpp != wp){
			for(int i=0; i<*wpp; ++i) std::cout << 1;
			++wpp;
		}
	}

	if(wpp != wp){
		for(int i=0; i<*wpp; ++i) std::cout << 1;
		++wpp;
	}
	if(zpp != zp){
		for(int i=0; i<*zpp; ++i) std::cout << 0;
		++zpp;
	}

	while(zpp != zp || wpp != wp){
		if(zpp != zp){
			for(int i=0; i<*zpp; ++i) std::cout << 0;
			++zpp;
		}
		if(wpp != wp){
			for(int i=0; i<*wpp; ++i) std::cout << 1;
			++wpp;
		}
	}

	std::cout << '\n';
}
