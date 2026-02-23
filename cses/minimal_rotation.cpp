#include <algorithm>
#include <iostream>
#include <string>
 
using ll = long long;
const int N = 1e6;

ll order[21][N], a[N], b[N];

int main(){
	std::string s; std::cin >> s;
	int n = s.size();

	for(int i=0; i<n; ++i) order[0][i] = s[i];

	for(int i=1; i<21; ++i){
		for(int j=0; j<n; ++j)
			a[j] = order[i][j] = order[i-1][j]*n + order[i-1][(j+(1<<(i-1)))%n];

		std::sort(a, a+n);

		int sz = 1;
		b[0] = a[0];
		for(int j=1; j<n; ++j)
			if(a[j] != a[j-1]) b[sz++] = a[j];

		int level = std::__lg(sz);
		for(int j=0; j<n; ++j){
			int p = 0;
			for(int s=1<<level; s; s/=2)
				if(p+s < sz && b[p+s] <= order[i][j]) p += s;
			order[i][j] = p;
		}
	}

	for(int i=0; i<n; ++i) if(!order[20][i]){
		for(int j=0; j<n; ++j) std::cout << s[(i+j)%n];
		std::cout << '\n';

		return 0;
	}
}
