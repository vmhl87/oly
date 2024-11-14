#include <iostream>

int b[1000][1000], c[1000][1001], d[1000][1001], e[1000][1000];
bool a[1000][1000];

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int n, m; std::cin >> n >> m;

	for(int i=0; i<n; ++i)
		for(int j=0; j<m; ++j){
			char c; std::cin >> c;
			a[i][j] = c == '*';
		}

	for(int i=0; i<n; ++i)
		for(int j=m-1, k=m; j>=0; --j){
			if(a[i][j]) k = j;
			e[i][j] = k;
		}

	for(int i=0; i<n; ++i){
		for(int l=0; l<m; ++l){
			for(int r=l; r<e[i][l]; ++r)
				++c[r-l][i-b[l][r]];
			for(int r=e[i][l]; r<m; ++r)
				b[l][r] = i+1;
		}
	}

	for(int i=0; i<m; ++i)
		for(int j=n, p=0; j>=0; --j)
			p += c[i][j], d[i][j] = p;
 
	for(int i=0; i<n; ++i)
		for(int j=0; j<m; ++j)
			std::cout << d[j][i] << " \n"[j==m-1];
}
