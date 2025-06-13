#include <iostream>

const int N = 2e5;

int root[30][N], e[N][3];

int find(int s, int i){
	if(root[s][i] < 0) return i;
	return root[s][i] = find(s, root[s][i]);
}

void unite(int s, int a, int b){
	if((a = find(s, a)) == (b = find(s, b))) return;
	if(root[s][a] < root[s][b]) root[s][a] += root[s][b], root[s][b] = a;
	else root[s][b] += root[s][a], root[s][a] = b;
}

int main(){
	int n, m; std::cin >> n >> m;

	for(int i=0; i<30; ++i)
		for(int j=0; j<n; ++j)
			root[i][j] = -1;

	for(int i=0; i<m; ++i){
		for(int j=0; j<3; ++j)
			std::cin >> e[i][j];
		--e[i][0], --e[i][1];
	}

	int mask = 0;

	for(int i=29; i>=0; --i){
		for(int j=0; j<m; ++j)
			if(((mask & e[j][2]) == 0) && (e[j][2] & (1 << i)) == 0)
				unite(i, e[j][0], e[j][1]);
		if(find(i, 0) == find(i, n-1)) mask |= 1 << i;
	}

	int res = 0;

	for(int i=0; i<30; ++i) if((mask & (1 << i)) == 0)
		res |= 1 << i;

	std::cout << res << '\n';
}
