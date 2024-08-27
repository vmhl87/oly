#include <algorithm>
#include <iostream>

int a[200000], b[200000];

int main(){
	int n, m, k; std::cin >> n >> m >> k;

	for(int i=0; i<n; ++i) std::cin >> a[i];
	for(int i=0; i<m; ++i) std::cin >> b[i];

	std::sort(a, a+n), std::sort(b, b+m);

	int p1=0, p2=0, res=0;

	while(p1 < n && p2 < m){
		if(a[p1] < b[p2]-k) ++p1;
		else if(a[p1] > b[p2]+k) ++p2;
		else ++p1, ++p2, ++res;
	}

	std::cout << res << '\n';
}
