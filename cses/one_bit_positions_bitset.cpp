#include <iostream>
#include <bitset>
#include <string>

const int N = 2e5;

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	std::bitset<N> a, b, c;
	std::string s; std::cin >> s;

	int p = 0;
	for(char c : s) a[p++] = c == '1';

	int n = s.length();
	b = a;

	for(int i=1; i<n; ++i){
		b <<= 1;
		c = a & b;
		std::cout << c.count() << " \n"[i==n-1];
	}
}
