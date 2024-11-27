#include <iostream>

int root[1000000], comp;

int find(int i){
	if(root[i] < 0) return i;
	return root[i] = find(root[i]);
}

void merge(int a, int b){
	if((a = find(a)) == (b = find(b))) return;
	--comp;

	if(root[a] < root[b]) root[a] += root[b], root[b] = a;
	else root[b] += root[a], root[a] = b;
}

int main(){
	int n, m; std::cin >> n >> m;
	comp = n; for(int i=0; i<n; ++i) root[i] = -1;

	for(int i=0; i<m; ++i){
		if(comp == 1) std::cout << i << '\n', exit(0);

		int a, b; std::cin >> a >> b;
		merge(a-1, b-1);
	}

	if(comp == 1) std::cout << m << '\n';
	else std::cout << -1 << '\n';
}
