#include <stdio.h>

int main(){
	char a, b, c;
	scanf("%c %c %c", &a, &b, &c);
	int counts[3] = {};
	if(a == '<') ++counts[1];
	else ++counts[0];
	if(b == '<') ++counts[2];
	else ++counts[0];
	if(c == '<') ++counts[2];
	else ++counts[1];
	if(counts[0] == 1) printf("A\n");
	if(counts[1] == 1) printf("B\n");
	if(counts[2] == 1) printf("C\n");
}
