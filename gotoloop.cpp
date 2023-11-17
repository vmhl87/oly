#include <stdio.h>

int main(){
	int i=0;
	start:
		if(i>10)return 0;
		printf("%d\n",i++);
	goto start;
}
