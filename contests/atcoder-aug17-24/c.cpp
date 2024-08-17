#include <iostream>

int r[8], c[8], n, k;

void recurse(int depth, int sum){
	if(depth == n){
		if(sum%k == 0){
			for(int i=0; i<n; ++i)
				std::cout << c[i] << " \n"[i==n-1];
		}
	}else{
		for(int i=1; i<=r[depth]; ++i){
			c[depth] = i;
			recurse(depth+1, sum+i);
		}
	}
}

int main(){
	std::cin >> n >> k;
	for(int i=0; i<n; ++i) std::cin >> r[i];

	recurse(0, 0);
}
