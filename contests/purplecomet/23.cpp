#include <iostream>
#include <numeric>

int order[11];
int fill[3] = {4, 4, 3};

bool work(){
	for(int i=0; i<9; ++i){
		if(order[i] == 2 && order[i+1] == 0) return 0;
		if(order[i] == 0 && order[i+1] == 2) return 0;
	}
	if(order[0] == 0) return 0;
	if(order[10] == 0) return 0;
	return 1;
}

int a, b;

void solve(){
	++b;
	if(work()) ++a;
}

void recurse(int i){
	if(i == 11){
		solve();

	}else{
		for(int j=0; j<3; ++j) if(fill[j]){
			--fill[j];
			order[i] = j;
			recurse(i+1);
			++fill[j];
		}
	}
}

int main(){
	recurse(0);
	std::cout << a << ' ' << b << ':' << std::gcd(a, b) << '\n';
}
