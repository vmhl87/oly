#include <iostream>
#include <vector>
#include <array>

using ll = long long;
const int maxn = 2e6 + 2;

std::vector<std::array<int, 2>> add[maxn], sub[maxn];

std::array<int, 2> tree[maxn*4];
int lazy[maxn*4];

void build(int i, int l, int r){
	if(l == r) ++tree[i][1];
	else{
		build(i*2, l, (l+r)/2);
		build(i*2+1, 1+(l+r)/2, r);
		tree[i][1] = tree[i*2][1] + tree[i*2+1][1];
	}
}

int count(int l, int r) { return tree[1][1]; }

void mod(int v, int i, int l, int r, int lb, int rb){
	if(lb > rb) return;
	else if(l == lb && r == rb) lazy[i] += v;
	//else if(l == r) lazy[i] += v;
	else{
		lazy[i*2] += lazy[i];
		lazy[i*2+1] += lazy[i];
		tree[i][0] += lazy[i];
		lazy[i] = 0;
		int m = (l+r)/2;
		mod(v, i*2,   l,   m, lb, std::min(rb, m));
		mod(v, i*2+1, 1+m, r, std::max(lb, 1+m), rb);
		if(tree[i*2][0] + lazy[i*2] < tree[i*2+1][0] + lazy[i*2+1])
			tree[i][1] = tree[i*2][1],
				tree[i][0] = tree[i*2][0] + lazy[i*2];
		else if(tree[i*2][0] + lazy[i*2] > tree[i*2+1][0] + lazy[i*2+1])
			tree[i][1] = tree[i*2+1][1],
				tree[i][0] = tree[i*2+1][0] + lazy[i*2+1];
		else tree[i][0] = tree[i*2][0] + lazy[i*2],
			tree[i][1] = tree[i*2][1] + tree[i*2+1][1];
	}
}

void inc(int l, int r) { mod(1, 1, 0, maxn-1, l, r); }
void dec(int l, int r) { mod(-1, 1, 0, maxn-1, l, r); }

int main(){
	int n; std::cin >> n;

	while(n--){
		int x1, y1, x2, y2; std::cin >> x1 >> y1 >> x2 >> y2;
		x1 += 1e6+1, y1 += 1e6+1, x2 += 1e6+1, y2 += 1e6+1;
		add[x1].push_back({y1, y2});
		sub[x2].push_back({y1, y2});
	}

	build(1, 0, maxn-1);

	ll res = 0;

	for(int i=0; i<maxn; ++i){
		res += maxn - count(0, maxn-1);
		for(const auto &[l, r] : add[i])
			inc(l, r-1);
		for(const auto &[l, r] : sub[i])
			dec(l, r-1);
	}

	std::cout << res << '\n';
}
