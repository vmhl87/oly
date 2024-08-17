#include <stdio.h>

int main(){
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);
	if(b<c){
		printf(a<b || a>=c ? "Yes\n" : "No\n");
	}else{
		printf(a<b && a>=c ? "Yes\n" : "No\n");
	}
}
