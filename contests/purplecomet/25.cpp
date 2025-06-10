#include <iostream>
#include <numeric>

int order[9];
int fill[3] = {3, 3, 3};

bool work(){
	int s[3] = {};
	for(int i=0; i<9; ++i)
		s[i/3] += order[i];
	if(s[0] == s[1] || s[0] == s[2] || s[1] == s[2]) return 1;
	return 0;
}

int a, b;

void solve(){
	++b;
	if(work()) ++a;
}

void recurse(int i){
	if(i == 9){
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
