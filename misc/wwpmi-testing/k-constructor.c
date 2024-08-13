#include <stdio.h>

long long f(long long n, long long k){
	if(k % 10000000 == 0) printf("%d%%\n", k/10000000);

	long long res = -1, pow = 1;

	for(; pow <= n; pow *= k) ++res;

	for(pow /= k; n; pow /= k) res += n/pow, n -= (n/pow) * pow;
	
	return res;
}

int main(){
	long long target = 10000000LL, sum = target;

	for(long long i=2; i<=target; ++i) sum += f(target, i);

	printf("%lld\n", sum);
}
