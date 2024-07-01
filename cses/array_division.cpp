#include <iostream>

typedef long long LL;

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int n, k; std::cin >> n >> k;

	int a[n]; for(int i=0; i<n; ++i) std::cin >> a[i];

	LL l = 0, r = 0;
	for(int x : a) r += (LL) x;
	l = r / (LL) k;

	while(l < r){
		LL mid = (l + r) >> 1;

		bool works = 1;
		int ranges = 1;
		LL current = 0;

		for(int x : a){
			if((LL) x > mid){
				works = 0;
				break;
			}

			if(current + (LL) x > mid) ++ranges, current = x;
			else current += (LL) x;
		}

		if(ranges > k) works = 0;

	if(works) r = mid;
		else l = mid+1;
	}

	std::cout << l << '\n';
}
