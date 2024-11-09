#include <iostream>
#include <vector>
#include <array>

std::array<int, 3> res[200000];
std::vector<int> adj[200000];
int a[200000], tree[400000], n;

int max(int l, int r){
	int res = a[r];
	for(l += n, r += n; l < r; l /= 2, r /= 2){
		if(l&1) res = std::max(res, tree[l++]);
		if(r&1) res = std::max(res, tree[--r]);
	}
	return res;
}

int main(){
	int q; std::cin >> n >> q;
	for(int i=0; i<n; ++i) std::cin >> a[i];
	for(int i=0; i<q; ++i) std::cin >> res[i][0] >> res[i][1],
		adj[--res[i][1]].push_back(i), --res[i][0];

	for(int i=0; i<n; ++i) tree[i+n] = a[i];
	for(int i=n-1; i; --i) tree[i] = std::max(tree[i*2], tree[i*2+1]);

	std::vector<int> s;

	for(int i=n-1; i>=0; --i){
		for(int x : adj[i]){
			int l = res[x][0],
				m = max(l+1, i);

			int r = -1;
			for(int j=1<<20; j; j/=2)
				if(r+j < s.size() && s[r+j] > m)
					r += j, res[x][2] += j;
		}

		while(s.size() && s.back() < a[i]) s.pop_back();
		s.push_back(a[i]);

	}

	for(int i=0; i<q; ++i) std::cout << res[i][2] << '\n';
}
