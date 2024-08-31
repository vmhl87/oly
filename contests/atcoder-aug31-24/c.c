#include <stdio.h>

int diff[200000];

int main(){
	int n; scanf("%d", &n);
	int v; scanf("%d", &v);
	for(int i=1; i!=n; ++i){
		int j; scanf("%d", &j);
		diff[i-1] = j-v, v = j;
	}

	int l = 0, r = 0;
	unsigned long long ans = n;

	for(; r!=n-1; ++r){
		while(diff[l] != diff[r]) ++l;
		ans += r-l+1;
	}

	printf("%zu\n", ans);
}
