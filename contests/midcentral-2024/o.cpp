#include <iostream>

int sqrt(int i){
	int res = 0;
	for(int x=1<<10; x; x/=2)
		if((x+res)*(x+res) <= i)
			res += x;
	return res;
}

const char *r[4] = {"EMPTY", "O", "S", "OS"};

void test(){
	int n; std::cin >> n;
	int t = 0; if(n&1) ++t;
	if(sqrt(n) * sqrt(n) == n) t += 2;

	std::cout << r[t] << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
