#include <iostream>

int v[500][500], i, j, n, m;
char x, p;

int main(){
	std::cin >> n >> m;

	for(i=0; i<n; ++i)
		for(j=0; j<m || (std::cout << '\n' && 0); ++j)
			std::cin >> x, p = 'A'+(i+j)%2,
				std::cout << (char)(p+(p==x)*2);
}
