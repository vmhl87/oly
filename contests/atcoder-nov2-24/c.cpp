#include <iostream>
#include <map>

std::map<int, int> pos;

int main(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i){
		int a; std::cin >> a;
		if(pos.count(a)) std::cout << pos[a]+1;
		else std::cout << -1;
		std::cout << " \n"[i==n-1];
		pos[a] = i;
	}
}
