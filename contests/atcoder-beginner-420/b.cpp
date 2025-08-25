#include <iostream>

char s[99][100];
int S[99];

int main(){
	int n, m; std::cin >> n >> m;
	for(int i=0; i<n; ++i) for(int j=0; j<m; ++j)
		std::cin >> s[i][j], s[i][j] -= '0';

	for(int i=0; i<m; ++i){
		int c[2] = {};
		for(int j=0; j<n; ++j)
			++c[s[j][i]];
		if(c[0] < c[1]) c[0] = 1, c[1] = 0;
		else c[0] = 0, c[1] = 1;
		for(int j=0; j<n; ++j)
			if(c[s[j][i]]) ++S[j];
	}

	int M = 0;
	for(int i=0; i<n; ++i) M = std::max(M, S[i]);

	for(int i=0; i<n; ++i) if(S[i] == M)
		std::cout << i+1 << ' ';
	std::cout << '\n';
}
