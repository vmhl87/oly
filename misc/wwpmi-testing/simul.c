#include <stdio.h>

const int M = 1000000007;

int main(){
	long long n = 1000000000;

	long long sum = ((n*(n+1))/2) % M;

	for(int i=1; i<n; ++i) sum = sum * 2 % M;

	printf("%lld\n", sum);
}
