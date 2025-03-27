#include <algorithm>
#include <iostream>
#include <string>

const int N = 1e6;

std::string s;
int n;

int order[N*2], L, r[2][N];

bool eq(int a, int b){
	if(!L) return s[a] == s[b];
	else{
		if(r[L&1][a] == r[L&1][b])
			return r[L&1][(a+(1<<(L-1)))%n] ==
				   r[L&1][(b+(1<<(L-1)))%n];
		return r[L&1][a] == r[L&1][b];
	}
}

bool cmp(int a, int b){
	if(!L) return s[a] < s[b];
	else{
		if(r[L&1][a] == r[L&1][b])
			return r[L&1][(a+(1<<(L-1)))%n] <
				   r[L&1][(b+(1<<(L-1)))%n];
		return r[L&1][a] <= r[L&1][b];
	}
}

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	std::cin >> s, n = s.length();

	for(int i=0; i<22; ++i){
		for(int j=0; j<n; ++j) order[(i&1)*n+j] = j;
		std::sort(order+(i&1)*n, order+(i&1)*n+n, cmp);
		//for(int j=0; j<n; ++j) std::cout << order[i&1][j] << " \n"[j==n-1];
		//for(int j=0; j<n; ++j){
		//	int p = order[i&1][j];
		//	for(int k=0; k<1<<i; ++k)
		//		std::cout << s[p], p = (p+1)%n;
		//	std::cout << " \n"[j==n-1];
		//}
		int p = 0;
		for(int j=1; j<n; ++j){
			if(!eq(order[(i&1)*n+j-1], order[(i&1)*n+j])) ++p;
			r[(i&1)^1][order[(i&1)*n+j]] = p;
		}
		++L;
	}

	std::string r = s;

	for(int i=0, j=order[(21&1)*n]; i<n; ++i, j=(j+1)%n)
		r[i] = s[j];
	std::cout << r << '\n';
}
