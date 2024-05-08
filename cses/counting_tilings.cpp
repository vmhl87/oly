#include <iostream>
using namespace std;

#define M 1000000007

void assign(int a, int i, int p, int v, int *next){
	if(i==1){
		next[p] = (next[p] + a) % M;
		return;
	}
	if(i&1){
		assign(a, i>>1, p, v<<1, next);
		return;
	}
	assign(a, i>>1, p|v, v<<1, next);
	if(!(i&1 || i&2)) assign(a, i>>2, p, v<<2, next);
}

void assign(int a, int i, int *next){
	assign(a, i, 0, 1, next);
}

int main(){
	int n, m; cin >> n >> m;
	int cur[1<<n] = {0}, next[1<<n] = {0};
	cur[0] = 1;
	while(m--){
		for(int i=0; i<1<<n; ++i)
			assign(cur[i], 1<<n|i, next);
		for(int i=0; i<1<<n; ++i)
			cur[i] = next[i], next[i] = 0;
	}
	cout << cur[0] << '\n';
}
