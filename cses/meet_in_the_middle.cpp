#include <algorithm>
#include <iostream>
#include <vector>

using ll = long long;

std::vector<ll> left, right;

int t[40];

int main(){
	int n, x; std::cin >> n >> x;
	for(int i=0; i<n; ++i) std::cin >> t[i];

	for(int i=0; i<1<<(n/2); ++i){
		ll now = 0;
		for(int j=0; j<n/2; ++j)
			if(i&(1<<j)) now += t[j];
		left.push_back(now);
	}

	for(int i=0; i<1<<(n-(n/2)); ++i){
		ll now = 0;
		for(int j=n/2; j<n; ++j)
			if(i&(1<<(j-(n/2)))) now += t[j];
		right.push_back(now);
	}

	std::sort(left.begin(), left.end());
	std::sort(right.begin(), right.end());

	ll res = 0;

	int p1 = right.size()-1, p2 = p1;

	for(ll i : left){
		while(p1 >= 0 && x-i <= right[p1]) --p1;
		while(p2 >= 0 && x-i < right[p2]) --p2;
		res += p2 - p1;
	}

	std::cout << res << '\n';
}
