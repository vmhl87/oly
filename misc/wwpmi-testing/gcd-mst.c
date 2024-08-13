#include <stdbool.h>
#include <stdio.h>

#define n 100000000

int next[n+1], prev[n+1], size = n+1;
bool rem[n+1];

int calls = 0;

void del(int i){
	if(rem[i]) return;
	next[prev[i]] = next[i];
	prev[next[i]] = prev[i];
	--size, rem[i] = 1;
}

int root[n+1];

int find(int i){
	if(root[i] < 0) return i;
	return root[i] = find(root[i]);
}

void merge(int a, int b){
	if((a = find(a)) == (b = find(b))) return;
	if(root[a] < root[b]) root[a] += root[b], root[b] = a;
	else root[b] += root[a], root[a] = b;
	calls += 2;
}

int main(){
	for(int i=0; i<n; ++i) next[i] = i+1; next[n] = 0;
	for(int i=0; i<n; ++i) prev[i+1] = i; next[0] = n;
	for(int i=0; i<=n; ++i) root[i] = -1;

	del(0), del(1);

	int at = 2, primes = 0;
	for(; size; ++primes){
		if(at*2 > n) calls += 3;
		else for(int i=at*2; i<=n; i+=at) merge(at, i), del(i);
		del(at), at = next[at];
	}

	printf("%d\n", calls);
}
