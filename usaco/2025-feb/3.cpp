#include <iostream>

bool e[16][16];

int main(){
	int n, m; std::cin >> n >> m;

	while(m--){
		int a, b; std::cin >> a >> b;
		e[--a][--b] = 1, e[b][a] = 1;
	}

	int best = 256;

	for(int i=0; i<1<<n; ++i){
		int cost = 0;

		for(int a=0; a<n; ++a)
			for(int b=a+1; b<n; ++b)
				if(!e[a][b]){
					if(((i&(1<<a)) == 0) != ((i&(1<<b)) == 0)) ++cost;
					if((i&(1<<a)) != 0 && (i&(1<<b)) != 0) ++cost;
				}else{
					if((i&(1<<a)) == 0 && (i&(1<<b)) == 0) ++cost;
				}
		
		best = std::min(best, cost);
	}

	for(int i=0; i<1<<n; ++i){
		int cost = 0;

		for(int a=0; a<n; ++a)
			for(int b=a+1; b<n; ++b)
				if(!e[a][b]){
					if(((i&(1<<a)) == 0) != ((i&(1<<b)) == 0)) ++cost;
				}else{
					if(((i&(1<<a)) == 0) == ((i&(1<<b)) == 0)) ++cost;
				}
		
		best = std::min(best, cost);
	}

	std::cout << best << '\n';
}
