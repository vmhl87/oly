#include <algorithm>
#include <iostream>
#include <cassert>

const int N = 1e5;

int a[N], count[31];

#define STRESS false

void test(){
	int n, k;

	if(STRESS){
		n = rand()&(1024-1); k = 1+(rand()%20);
		std::cout << n << ' ' << k << '\n';

	}else{
		std::cin >> n >> k;
	}

	for(int i=0; i<k; ++i) a[i] = n;
	for(int i=0; i<31; ++i) count[i] = 0;

	for(int j=30; j>=0; --j){
		int current = 0;

		if(n&(1<<j)){
			// need odd #
			for(int i=0; i<k; ++i) if(a[i]&(1<<j)) ++current;
			int possible = 0;
			for(int i=0; i<k; ++i) if(!(a[i]&(1<<j)) && (a[i]|(1<<j)) <= n) ++possible;

			int goal = (current+possible)-1+((current+possible)&1);

			if(goal == -1){ // implies current=0, possible=0?
				for(int x=j+1; x<31; ++x) if(count[x] >= 2){
					for(int i=0; i<k; ++i) if(a[i]&(1<<x)){
						a[i] ^= 1<<x;
						a[i] ^= 1<<j;
						--count[x];
						break;
					}

					for(int i=0; i<k; ++i) if(a[i]&(1<<x)){
						a[i] ^= 1<<x;
						--count[x];
						break;
					}

					goal = 1; current = 1;
					break;
				}
			}

			assert(goal >= 0);

			if(goal < current) for(int i=0; i<k; ++i)
				if((a[i]&(1<<j)) && goal < current) a[i] ^= 1<<j, --current;

			if(goal > current) for(int i=0; i<k; ++i)
				if(!(a[i]&(1<<j)) && goal > current) a[i] ^= 1<<j, ++current;

		}else{
			// need even #
			for(int i=0; i<k; ++i) if(a[i]&(1<<j)) ++current;
			int possible = 0;
			for(int i=0; i<k; ++i) if(!(a[i]&(1<<j)) && (a[i]|(1<<j)) <= n) ++possible;

			int goal = (current+possible)-((current+possible)&1);

			assert(goal >= 0);

			if(goal < current) for(int i=0; i<k; ++i)
				if((a[i]&(1<<j)) && goal < current) a[i] ^= 1<<j, --current;

			if(goal > current) for(int i=0; i<k; ++i)
				if(!(a[i]&(1<<j)) && goal > current) a[i] ^= 1<<j, ++current;
		}

		count[j] = current;

		std::sort(a, a+k, [] (int x, int y) { return x > y; });
	}

	for(int i=0; i<k; ++i) std::cout << a[i] << " \n"[i==k-1];
}

int main(){
	if(STRESS){
		// srand(time(NULL)); while(true) test();
	
	}else{
		int t; std::cin >> t;
		while(t--) test();
	}
}
