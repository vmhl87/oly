#include <stdlib.h>
#include <stdio.h>

int main(){
	unsigned int start, target, n;
	scanf("%d %d %d", &start, &target, &n);

	// intial bounds:
	//   low is obviously `start`
	//   high is like perf required to get start -> target in
	//   1 contest trust
	
	unsigned int l = start, r = start + (target - start) * 4;
								// will check if becomes shl trust
	
	while(l < r){
		unsigned int m = (l+r)/2;

		// will be a little pessimistic bc ints but wtv
		unsigned int now = start;
		for(unsigned int i=0; i<n; ++i)
			now += (m - now) / 4;  // should be shr

		if(now >= target) r = m;
		else l = m+1;
	}

	printf("Minimum required perf: %d\n", l);
}
