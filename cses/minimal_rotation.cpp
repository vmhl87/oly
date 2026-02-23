#include <algorithm>
#include <iostream>
#include <string>
 
using ll = long long;
const int N = 1e6;

ll order[N], b[N];
int a[N];

int main(){
	std::cin.tie(0)->sync_with_stdio(0);

	std::string s; std::cin >> s;
	int n = s.size();

	for(int i=0; i<n; ++i) order[i] = s[i];

	for(int i=1; i<=20; ++i){
		for(int j=0; j<n; ++j)
			b[j] = order[j]*n + order[(j+(1<<(i-1)))%n], a[j] = j;

		std::sort(a, a+n, [](int x, int y){ return b[x] < b[y]; });

		for(int j=0, p=0; j<n; ++j){
			if(j && b[a[j]] != b[a[j-1]]) ++p;
			order[a[j]] = p;
		}
	}

	for(int i=0; i<n; ++i) if(!order[i]){
		std::string o(n, 0);
		for(int j=0; j<n; ++j) o[j] = s[(i+j)%n];
		std::cout << o << '\n';

		return 0;
	}
}
