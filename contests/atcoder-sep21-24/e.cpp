#include <iostream>

int root[200000], order[200000][10];

int find(int i){
	if(root[i] < 0) return i;
	return root[i] = find(root[i]);
}

void addto(int a[10], int b){
	if(b > a[9]){
		a[9] = b;
		for(int i=9; i; --i){
			if(a[i] > a[i-1]) std::swap(a[i], a[i-1]);
		}
	}
}

void merge(int a, int b){
	int next[10]; for(int i=0; i<10; ++i) next[i] = -1;
	for(int i=0; i<10; ++i) addto(next, order[a][i]), addto(next, order[b][i]);
	for(int i=0; i<10; ++i) order[a][i] = next[i];
}

void unite(int a, int b){
	if(a == b) return;
	if(root[a] < root[b]){
		merge(a, b);
		root[a] += root[b];
		root[b] = a;
	}else{
		merge(b, a);
		root[b] += root[a];
		root[a] = b;
	}
}

int main(){
	int n, q; std::cin >> n >> q;

	for(int i=0; i<n; ++i){
		root[i] = -1;
		order[i][0] = i+1;
		for(int j=1; j<10; ++j)
			order[i][j] = -1;
	}

	while(q--){
		int t, a, b; std::cin >> t >> a >> b;

		if(t&1) unite(find(a-1), find(b-1));
		else std::cout << order[find(a-1)][b-1] << '\n';
	}
}
