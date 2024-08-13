// Brute force all combinations, essentially

#include <iostream>
#include <array>
#include <set>

int a[7], n, val[7];  // a, b, c, bc, ac, ab, abc
std::set<std::array<int, 3>> count;
bool use[7];

void permute(int d){
	if(d == n){
		int c[3] = {};
		for(int i=0; i<3; ++i) if(use[i]){
			if(c[i] && c[i] != val[i]) goto fail;
			c[i] = val[i];
			for(int j=0; j<3; ++j) if(j!=i && use[j+3]){
				int k = 3-i-j, m = val[j+3] - val[i];
				if(c[k] && c[k] != m) goto fail;
				c[k] = m;
			}
		}
		if(use[6]) for(int i=0; i<3; ++i) if(use[i+3]){
			int m = val[6] - val[3+i];
			if(c[i] && c[i] != m) goto fail;
			c[i] = m;
		}
		for(int i=0; i<3; ++i) if(c[i] <= 0) goto fail;
		for(int i=0; i<2; ++i) if(c[i] > c[i+1]) goto fail;
		for(int i=0; i<3; ++i) if(use[i+3] && val[i+3] !=
				c[0]+c[1]+c[2]-c[i]) goto fail;
		if(use[6] && val[6] != c[0]+c[1]+c[2]) goto fail;
		count.insert({c[0], c[1], c[2]});
fail:
		return;
	}else{
		for(int i=0; i<7; ++i) if(!use[i]){
			use[i] = 1;
			val[i] = a[d];
			permute(d+1);
			use[i] = 0;
		}
	}
}

void test_case(){
	std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> a[i];

	count.clear(), permute(0);
	std::cout << count.size() << '\n';
}

int main(){
	int t; std::cin >> t;
	while(t--) test_case();
}
