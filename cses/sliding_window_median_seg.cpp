#include <algorithm>
#include <iostream>
#include <array>

const int N = 1<<18;

std::array<int, 2> a[N];
int b[N], t[N*2][2];

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int n, k; std::cin >> n >> k;
	for(int i=0; i<n; ++i) std::cin >> a[i][0], a[i][1] = i;
	std::sort(a, a+n);

	for(int i=0; i<n; ++i) t[i+N][1] = a[i][0], b[a[i][1]] = i;

	for(int i=0; i<k; ++i)
		for(int j=b[i]+N; j; j/=2)
			++t[j][0];

	for(int i=k; i<=n; ++i){
		int r = 1, l = (1+k)/2;
		while(l > 0 && r < N){
			if(l > t[r*2][0]) l -= t[r*2][0], r = r*2+1;
			else r = r*2;
		}
		std::cout << t[r][1] << " \n"[i==n];
		if(i < n){
			for(int j=b[i]+N; j; j/=2)
				++t[j][0];
			for(int j=b[i-k]+N; j; j/=2)
				--t[j][0];
		}
	}
}
