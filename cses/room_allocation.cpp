#include <algorithm>
#include <iostream>
#include <vector>
#include <array>

std::vector<std::array<int, 2>> ev;
int res[200001];

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int n; std::cin >> n;
	ev.reserve(n*2);

	for(int i=0; i<n; ++i){
		int start, end; std::cin >> start >> end;
		ev.push_back({start, -1-i});
		ev.push_back({end, 1+i});
	}

	std::sort(ev.begin(), ev.end());

	std::vector<int> empty;
	int now = 0;

	for(const auto &[t, x] : ev){
		if(x > 0) empty.push_back(res[x]);
		else{
			if(empty.size()) res[-x] = empty.back(),
				empty.pop_back();
			else res[-x] = ++now;
		}
	}

	std::cout << now << '\n';
	for(int i=1; i<=n; ++i) std::cout << res[i] << " \n"[i==n];
}
