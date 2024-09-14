#include <stdio.h>

int main(){
	int n; scanf("%d", &n);
	int diff = 0;
	char first; scanf("%c", &first);
	for(int i=1; i<n; ++i){
		char now; scanf("%c", &now);
		if(now != first) ++diff;
		first = now;
	}
	printf("%d\n", (diff+1)/2);
}
