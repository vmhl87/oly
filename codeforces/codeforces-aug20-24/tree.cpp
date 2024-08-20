#include <iostream>
#include <map>

std::map<int, int> par;

void find(int a, int b){
	std::cout << "? " << a << ' ' << b << '\n';
	std::cout.flush();
	int res; std::cin >> res;
	if(res == a) par[b] = a;
	else{
		if(!par.count(res)) find(a, res);
		find(res, b);
	}
}

void test_case(){
	int n; std::cin >> n;
	par.clear();
	for(int i=2; i<=n; ++i) find(1, i);
	std::cout << "! ";
	for(const auto &[a, b] : par)
		std::cout << a << ' ' << b << ' ';
	std::cout << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test_case();
}
