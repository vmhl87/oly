#include <iostream>

int v[200];

void test(){
	int n, m; std::cin >> n >> m;

	for(int i=0; i<m; ++i) v[i] = 0;

	for(int i=0; i<n; ++i)
		for(int j=0; j<m; ++j){
			char x; std::cin >> x;
			int y = 0;
			if(x != '.') y = x - '0';
			v[j] = std::max(v[j], y);
		}

	int sum = 0;
	for(int i=0; i<m; ++i) sum += v[i];
	std::cout << sum << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
