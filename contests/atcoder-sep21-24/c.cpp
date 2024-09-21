#include <iostream>
#include <string>

std::string s;
int n, now;

void cons(int i, int d){
	if(i<0 || i+2>=n) return;
	if(s[i] == 'A' && s[i+1] == 'B' && s[i+2] == 'C')
		now += d;
}

int main(){
	int q;
	std::cin >> n >> q >> s;

	for(int i=0; i<n; ++i) cons(i, 1);

	while(q--){
		int x; char c; std::cin >> x >> c, --x;

		cons(x-2, -1), cons(x-1, -1), cons(x, -1);

		s[x] = c;

		cons(x-2, 1), cons(x-1, 1), cons(x, 1);

		std::cout << now << '\n';
	}
}
