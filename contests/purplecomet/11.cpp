#include <iostream>

int main(){
	int res = 0;
	for(int m=1; m<=104; ++m){
		for(int n=1; n<=104-m; ++n){
			for(int p=1; p<=104-m-n; ++p){
				if(m+n+p == 104){
					if(4*n*m + 4*n*p + 4*m*p == m*n*p){
						int thonk = std::max(m, std::max(n, p));
						if(thonk > res){
							res = thonk;
							std::cout << m << ' ' << n << ' ' << p << '\n';
						}
					}
				}
			}
		}
	}
	std::cout << res << '\n';
}
