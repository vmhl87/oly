#include <iostream>

int a[100], n;

bool w(int x){
	int c = 0;
	for(int i=0; i<n; ++i)
		if(a[i] >= x) ++c;
	return c >= x;
}

int main(){
	std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> a[i];

	int x = 0;

	for(int s=1<<30; s; s/=2)
		if(w(x+s)) x += s;

	std::cout << x << '\n';
}
