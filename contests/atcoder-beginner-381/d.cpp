#include <iostream>

int a[200002], b[200002], r = 0, l = 0, c[200002];

void clear(){
	while(l<r) c[b[l++]] = 0;
	l = 0, r = 0;
}

int push(int x){
	b[r++] = x;
	++c[x];
	while(c[x] > 1) --c[b[l++]];
	return (r-l)*2;
}

int main(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> a[i];

	int best = 0;

	for(int i=0; i+1<n; i+=2)
		if(a[i] != a[i+1]) clear();
		else best = std::max(best, push(a[i]));

	clear();

	for(int i=1; i+1<n; i+=2)
		if(a[i] != a[i+1]) clear();
		else best = std::max(best, push(a[i]));

	std::cout << best << '\n';
}
