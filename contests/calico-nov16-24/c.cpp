#include <iostream>

char a[100][100];

void test_case(){
	int n, m; std::cin >> n >> m;
	for(int i=0; i<n; ++i)
		for(int j=0; j<m; ++j)
			std::cin >> a[i][j];

	int lx = n, ly = m, rx = 0, ry = 0, ct = 0;
	
	for(int i=0; i<n; ++i)
		for(int j=0; j<m; ++j) if(a[i][j] == '#'){
			lx = std::min(lx, i);
			rx = std::max(rx, i);
			ly = std::min(ly, j);
			ry = std::max(ry, j);
			++ct;
		}

	if((rx-lx+1) * (ry-ly+1) == ct) std::cout << "ferb";
	else std::cout << "phineas";
	std::cout << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test_case();
}
