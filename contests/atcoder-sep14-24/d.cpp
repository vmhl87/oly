#include <iostream>
#include <array>

using ll = long long;

// count, left index, right index
std::array<ll, 3> tree[800000];
std::array<ll, 2> vill[200000];

void build(int i, int l, int r){
	if(l==r){
		tree[i][0] = vill[l][1];
		for(int j=1; j<3; ++j)
			tree[i][j] = vill[l][0];
	}else{
		int mid = (l+r)/2;
		build(i*2, l, mid);
		build(i*2+1, mid+1, r);
		tree[i][0] = tree[i*2][0] + tree[i*2+1][0];
		tree[i][2] = tree[i*2+1][2];
		tree[i][1] = tree[i*2][1];
	}
}

ll count(int i, int l, int r){
	if(l<=tree[i][1] && r>=tree[i][2]) return tree[i][0];
	if(l>tree[i][2] || r<tree[i][1]) return 0;
	return count(i*2, l, r) + count(i*2+1, l, r);
}

int main(){
	int n; std::cin >> n;

	for(int i=0; i<n; ++i) std::cin >> vill[i][0];
	for(int i=0; i<n; ++i) std::cin >> vill[i][1];

	build(1, 0, n-1);

	int q; std::cin >> q;

	while(q--){
		ll l, r; std::cin >> l >> r;

		std::cout << count(1, l, r) << '\n';
	}
}
