// CCO '13 P2 Tourney  -  https://dmoj.ca/problem/cco13p2

#include <iostream>
#include <array>

constexpr int MAXN = 1<<20;

std::array<int, 2> tree[MAXN*2];
int wins[MAXN];

int main(){
	int n, m; std::cin >> n >> m;

	const int OFF = 1<<n;

	for(int i=0; i<(1<<n); ++i) std::cin >> tree[i+OFF][0], tree[i+OFF][1] = i;
	for(int i=OFF-1; i; --i){
		int level = n - (std::__lg(i));
		if(tree[i<<1][0] > tree[i<<1|1][0]){
			tree[i][0] = tree[i<<1][0];
			tree[i][1] = tree[i<<1][1];
			wins[tree[i<<1][1]] = level;
			wins[tree[i<<1|1][1]] = level-1;
		}else{
			tree[i][0] = tree[i<<1|1][0];
			tree[i][1] = tree[i<<1|1][1];
			wins[tree[i<<1|1][1]] = level;
			wins[tree[i<<1][1]] = level-1;
		}
	}

	while(m--){
		char t; std::cin >> t;

		if(t == 'R'){
			int i, s; std::cin >> i >> s, --i;
			tree[i+OFF][0] = s;
			for(i = (i+OFF)/2; i; i >>= 1){
				if(tree[i<<1][0] > tree[i<<1|1][0]){
					tree[i][0] = tree[i<<1][0];
					tree[i][1] = tree[i<<1][1];
					wins[tree[i<<1][1]] = n-std::__lg(i);
					wins[tree[i<<1|1][1]] = n-std::__lg(i)-1;
				}else{
					tree[i][0] = tree[i<<1|1][0];
					tree[i][1] = tree[i<<1|1][1];
					wins[tree[i<<1|1][1]] = n-std::__lg(i);
					wins[tree[i<<1][1]] = n-std::__lg(i)-1;
				}
			}

		}else if(t == 'W'){
			std::cout << tree[1][1]+1 << '\n';

		}else{
			int i; std::cin >> i, --i;
			std::cout << wins[i] << '\n';
		}
	}
}
