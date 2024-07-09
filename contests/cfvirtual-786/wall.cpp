#include <iostream>

int main(){
	int n; std::cin >> n;
	int a[n]; for(int i=0; i<n; ++i) std::cin >> a[i];

	int opt[2] = {0, 1};
	if(a[0] < a[1]) opt[0] = 1, opt[1] = 0;

	for(int i=2; i<n; ++i){
		if(a[i] < a[opt[0]]) opt[0] = i;
		if(a[opt[0]] < a[opt[1]]) opt[0] = opt[1], opt[1] = i;
	}

	auto consider = [&](int i, int j){
		if(std::abs(i - j) == 1){
			int ret = std::abs(a[i] - a[j]);
			if(ret > std::min(a[i], a[j])){
				return (std::max(a[i], a[j])+1)/2;
			}
			int c = std::min(a[i], a[j]) - ret;
			return ret + 2*(c/3) + c%3;
		}else if(std::abs(i - j) == 2){
			return std::min(a[i], a[j]) + (std::abs(a[i] - a[j])+1)/2;
		}else{
			return (a[i]+1)/2 + (a[j]+1)/2;
		}
	};

	int res = consider(opt[0], opt[1]);
	for(int i=1; i<n; ++i) res = std::min(res, consider(i-1, i));
	for(int i=2; i<n; ++i) res = std::min(res, consider(i-2, i));

	std::cout << res << '\n';
}
