#include <iostream>
#include <vector>

int to[200000], res[200000], h[200000];

void path(int i){
	if(to[i] == -1) { res[i] = 0; return; }
	else if(res[to[i]] == -1) path(to[i]);
	res[i] = res[to[i]] + 1;
}

int main(){
	int n; std::cin >> n;

	for(int i=0; i<n; ++i) to[i] = -1, res[i] = -1, std::cin >> h[i];

	int stack = -1;

	for(int i=n-1; i>=0; --i){
		while(stack != -1 && h[i] > h[stack]) stack = to[stack];
		to[i] = stack, stack = i;
	}

	for(int i=0; i<n; ++i) if(res[i] == -1) path(i);

	for(int i=0; i<n-1; ++i) std::cout << 1+res[i+1] << ' ';
	std::cout << 0 << '\n';
}
