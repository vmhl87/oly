#include <algorithm>
#include <iostream>
#include <numeric>
#include <array>
#include <map>

std::array<int, 2> add[150000], rem[150000];
int out[150000];

int main(){
	int n, m; std::cin >> n >> m;

	int p1 = 0, p2 = 0;
	for(int i=0; i<m; ++i){
		int x, y, z; std::cin >> x >> y >> z;
		add[p1][0] = x-1, add[p1++][1] = z;
		rem[p2][0] = y-1, rem[p2++][1] = z;
	}

	std::sort(add, add+p1), std::sort(rem, rem+p2);

	p1 = 0, p2 = 0;
	std::map<int, int> req;

	for(int i=0; i<n; ++i){
		while(add[p1][0] == i){
			if(req.count(add[p1][1])) ++req[add[p1][1]];
			else{
				if(req.size()){
					int b = (--req.end())->first;
					if(std::gcd(b, add[p1][1]) != std::min(b, add[p1][1])){
						std::cout << "Impossible\n";
						return 0;
					}
				}
				++req[add[p1][1]];
			}
			++p1;
		}

		if(req.size()) out[i] = (--req.end())->first;
		else out[i] = 1;

		while(rem[p2][0] == i){
			if(req[rem[p2][1]] == 1) req.erase(rem[p2][1]);
			else --req[rem[p2][1]];
			++p2;
		}
	}

	for(int i=0; i<n; ++i) std::cout << out[i] << " \n"[i==n-1];
}
