#include <stdio.h>

int main(){
	long long res = 0, target = 1000000000000000000;

	while(target) res += target, target /= 2;

	printf("%lld\n", res);
}
