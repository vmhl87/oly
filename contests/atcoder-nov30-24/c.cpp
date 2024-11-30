#include <iostream>

const int N = 2e5;

int a[N];

int main(){
	int n, m; std::cin >> n >> m;

	for(int i=0; i<n; ++i){
		std::cin >> a[i];
		if(i) a[i] = std::min(a[i], a[i-1]);
	}

	for(int i=0; i<m; ++i){
		int x; std::cin >> x;

		if(x < a[n-1]) std::cout << -1 << '\n';
		else{
			int j = n-1;
			for(int y=1<<18; y; y/=2)
				if(j-y>=0 && a[j-y] <= x)
					j -= y;
			std::cout << j+1 << '\n';
		}
	}
}
