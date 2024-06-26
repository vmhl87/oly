#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

void test_case(){
	int n, k; std::cin >> n >> k;

	std::map<int, std::vector<int>> sect;

	for(int i=0; i<n; ++i){
		int x; std::cin >> x;

		sect[x % k].push_back(x/k);
	}

	int oddcount = 0;

	for(const auto &[a, b] : sect)
		oddcount += b.size() & 1,
			std::sort(sect[a].begin(), sect[a].end());

	if(oddcount > 1){
		std::cout << -1 << '\n';
		return;
	}

	long long res = 0;

	for(const auto &[_, v] : sect){
		long long sum = 0;

		for(int i=0; i<v.size()-1; i+=2) sum += v[i+1]-v[i];

		if(v.size() & 1){
			long long base = sum;

			for(int i=v.size()-2; i>0; i-=2){
				base += v[i+1]-v[i];
				base -= v[i]-v[i-1];

				if(base < sum) sum = base;
			}
		}

		res += sum;
	}

	std::cout << res << '\n';
}

int main(){
	int t; std::cin >> t;

	while(t--) test_case();
}
