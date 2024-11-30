#include <iostream>
#include <vector>
#include <array>

std::vector<std::array<int, 12>> res;

std::array<int, 12> build;
int n, m, maxn;

void recurse(int i){
	if(i == n){
		if(build[n-1] <= m)
			res.push_back(build);
	}else{
		for(int j=build[i-1]+10; j<=maxn+i*10; ++j)
			build[i] = j, recurse(i+1);
	}
}

int main(){
	std::cin >> n >> m;

	maxn = m - (n-1) * 10;

	for(int i=1; i<=maxn; ++i)
		build[0] = i, recurse(1);

	std::cout << res.size() << '\n';

	for(auto x : res)
		for(int i=0; i<n; ++i)
			std::cout << x[i] << " \n"[i==n-1];
}
