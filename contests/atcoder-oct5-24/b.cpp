#include <iostream>
#include <cstdio>

char aa[200], bb[200];

int main(){
	scanf("%s", &aa);
	scanf("%s", &bb);
	char *a = aa, *b = bb;
	int pos = 1;
	while(1){
		if(*a != *b) std::cout << pos << '\n', exit(0);
		if(*a == 0) std::cout << 0 << '\n', exit(0);
		++pos, ++a, ++b;
	}
}
