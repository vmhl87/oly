#include <iostream>

int main(){
	int n; std::cin >> n;

	int l, r; std::cin >> l >> r;

	for(int i=1; i<n; ++i){
		int a, b; std::cin >> a >> b;
		l = std::max(l, a), r = std::min(r, b);
	}

	if(l > r) std::cout << "bad news";
	else std::cout << (r-l+1) << ' ' << l;
	std::cout << '\n';
}
