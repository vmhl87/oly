#include <iostream>

using LL = long long;

int a[5001], b[5001];
LL p[10004];

int main(){
	int n, m; std::cin >> n >> m;

	while(n--){
		int c, d; std::cin >> c >> d, ++a[c], ++b[d];
	}

	for(int i=0; i<=m; ++i){
		p[i*2] += (LL)a[i]*a[i];
		p[1+i*2] -= (LL)b[i]*b[i];

		for(int j=i+1; j<=m; ++j){
			p[i+j] += (LL)a[i]*a[j]*2;
			p[i+j+1] -= (LL)b[i]*b[j]*2;
		}
	}

	LL curr = 0;
	for(int i=0; i<=m*2; ++i) curr += p[i], std::cout << curr << '\n';
}
