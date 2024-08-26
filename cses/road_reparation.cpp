#include <algorithm>
#include <iostream>
#include <vector>
#include <array>

using ll = long long;

std::array<int, 3> edges[200000];

int root[100000];

int find(int i){
	if(root[i] < 0) return i;
	return root[i] = find(root[i]);
}

int main(){
	int n, m; std::cin >> n >> m;

	for(int i=0; i<m; ++i)
		std::cin >> edges[i][1] >> edges[i][2] >> edges[i][0],
			--edges[i][1], --edges[i][2];
	
	std::sort(edges, edges+m);

	for(int i=0; i<n; ++i) root[i] = -1;

	ll cost = 0;
	int count = 0;

	for(int i=0; i<m; ++i){
		int a = find(edges[i][1]), b = find(edges[i][2]);
		if(a != b){
			++count;
			cost += edges[i][0];
			if(root[a] < root[b]) root[a] += root[b], root[b] = a;
			else root[b] += root[a], root[a] = b;
		}
	}

	if(count != n-1) std::cout << "IMPOSSIBLE\n";
	else std::cout << cost << '\n';
}
