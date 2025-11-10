#include <iostream>

const int N = 2e5;

int root[N], count[N];
bool b[N];

int find(int i){
	if(root[i] < 0) return i;
	return root[i] = find(root[i]);
}

void merge(int a, int b){
	if((a = find(a)) == (b = find(b))) return;
	if(root[a] < root[b]) root[a] += root[b], count[a] += count[b], root[b] = a;
	else root[b] += root[a], count[b] += count[a], root[a] = b;
}

int main(){
	int n, q; std::cin >> n >> q;
	for(int i=0; i<n; ++i) root[i] = -1;

	while(q--){
		int t; std::cin >> t;

		if(t == 1){
			int u, v; std::cin >> u >> v;
			merge(u-1, v-1);

		}else if(t == 2){
			int v; std::cin >> v, --v;
			if(b[v]) b[v] = 0, --count[find(v)];
			else b[v] = 1, ++count[find(v)];

		}else{
			int v; std::cin >> v, --v;
			std::cout << (count[find(v)] ? "Yes\n" : "No\n");
		}
	}
}
