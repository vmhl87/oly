#include <stdio.h>

int main(){
	for(int i=1; i<1001; ++i)
		for(int j=0; j<1000; ++j)
			printf(" %d", 107897 * i + j);
}
