#include <iostream>

const int N = 101;

int a[N];

int main(){
	int n, s; std::cin >> n >> s;
	for(int i=0; i<n; ++i) std::cin >> a[i+1];
	++n;

	for(int i=1; i<n; ++i) if(a[i]-a[i-1] > s){
		std::cout << "No\n";
		return 0;
	}

	std::cout << "Yes\n";
}
