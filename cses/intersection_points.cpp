#include <algorithm>
#include <iostream>
#include <vector>
#include <array>

using ll = long long;
const int N = 1e5;

std::vector<std::array<int, 4>> ev;
std::vector<int> idx;
int t[N*2];

int o(int i){
	int r = idx.size();
	for(int s=1<<17; s; s/=2)
		if(r >= s && idx[r-s] >= i)
			r -= s;
	return r;
}

int main(){
	int n; std::cin >> n;

	while(n--){
		int x1, y1, x2, y2; std::cin >> x1 >> y1 >> x2 >> y2;
		
		if(x1 == x2){
			ev.push_back({x1, y1, y2, 0});
		}else{
			idx.push_back(y1);
			ev.push_back({x1, y1, 1, 1});
			ev.push_back({x2, y1, 1, 1});
		}
	}

	n = idx.size();

	std::sort(ev.begin(), ev.end());
	std::sort(idx.begin(), idx.end());

	ll res = 0;

	for(auto &x : ev)
		if(x[3]){
			int i = o(x[1]);
			t[i+n] ^= 1;
			for(i=(i+n)/2; i; i/=2)
				t[i] = t[i*2] + t[i*2+1];
		}else{
			int l = o(x[1]), r = o(x[2]+1);
			for(l+=n, r+=n; l<r; l/=2, r/=2){
				if(l&1) res += t[l++];
				if(r&1) res += t[--r];
			}
		}

	std::cout << res << '\n';
}
