#include <iostream>

const int N = 1e5;

char a[N];

void test(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> a[i];

	for(int p=0, f=0; p<n-1; ++p){
		if(a[p] > a[p+1]){
			f = 1;
			char x = a[p];
			a[p] = a[p+1];
			a[p+1] = x;

		}else if(f) break;
	}

	for(int i=0; i<n; ++i) std::cout << a[i];
	std::cout << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test();
}
