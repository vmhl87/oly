#include <iostream>

int main(){
	int n, q; std::cin >> n >> q;

	while(q--){
		int k; std::cin >> k;
		int match = n*n-k;

		bool find = 0;
		for(int i=2; i<=n; ++i)
			if(match % i == 0 && match / i <= n && match / i >= 2)
				find = 1;

		if(match == 0) find = 1;

		std::cout << (find ? "Yes" : "No") << '\n';
	}
}
