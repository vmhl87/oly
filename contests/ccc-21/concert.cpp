#include <iostream>

using LL = long long;

int n, p[200000], w[200000], d[200000];

LL at(int l){
	LL ret = 0;

	for(int i=0; i<n; ++i) if(std::abs(l - p[i]) > d[i])
		ret += (LL)w[i] * (std::abs(l - p[i]) - d[i]);

	return ret;
}

int main(){
	std::cin >> n;

	for(int i=0; i<n; ++i)
		std::cin >> p[i] >> w[i] >> d[i];

	int l = 0, r = 0;
	for(int i=0; i<n; ++i) if(p[i] > r) r = p[i];

	while(l < r){
		int m = (l+r)/2, mm = m+1;

		if(at(m) < at(mm)) r = m;
		else l = mm;
	}

	std::cout << at(l) << '\n';
}
