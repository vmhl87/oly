#include <algorithm>
#include <iostream>
#include <vector>

const int N = 2e5;

int a[N], t[N*2], l[N], r[N], b[N], n;

int rmq(int l, int r){
	int res = 0;
	for(l+=n, r+=n; l<r; l/=2, r/=2){
		if(l&1) res = std::max(res, t[l++]);
		if(r&1) res = std::max(res, t[--r]);
	}
	return res;
}

int main(){
	std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> a[i];

	{
		std::vector<int> s;
		for(int i=0; i<n; ++i){
			while(s.size() && a[s.back()] < a[i]) s.pop_back();
			l[i] = s.size() ? s.back() : -1;
			s.push_back(i);
		}
	};

	{
		std::vector<int> s;
		for(int i=n-1; i>=0; --i){
			while(s.size() && a[s.back()] < a[i]) s.pop_back();
			r[i] = s.size() ? s.back() : n;
			s.push_back(i);
		}
	};

	for(int i=0; i<n; ++i) b[i] = i;
	std::sort(b, b+n, [] (int x, int y) { return a[x] < a[y]; });

	for(int i=0; i<n*2; ++i) t[i] = 1;

	for(int i=0; i<n; ++i){
		t[b[i]+n] = std::max(rmq(l[b[i]]+1, b[i]), rmq(b[i]+1, r[b[i]])) + 1;
		for(int j=(b[i]+n)/2; j; j/=2) t[j] = std::max(t[j*2], t[j*2+1]);
	}

	std::cout << t[1] << '\n';
}
