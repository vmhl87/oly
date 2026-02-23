#include <iostream>

using ll = long long;
const int N = 1e6;

bool sieve[N];
int x[N];

int root[N];

int find(int i){
	if(root[i] < 0) return i;
	return root[i] = find(root[i]);
}

void unite(int a, int b){
	a = find(a), b = find(b);
	if(a == b) return;

	if(root[a] < root[b]) root[a] += root[b], root[b] = a;
	else root[b] += root[a], root[a] = b;
}

int main(){
	int n; std::cin >> n;
	for(int i=0; i<n; ++i) std::cin >> x[i], root[i] = -1;

	for(int i=2; i<1e6; ++i) sieve[i] = 1;
	for(int i=2; i<1e6; ++i) if(sieve[i])
		for(int j=i+i; j<1e6; j+=i) sieve[j] = 0;

	for(int i=0; i<1e6; ++i) if(sieve[i]){
		for(int j=0, l=-1; j<n; ++j) if(x[j]%i == 0){
			if(l+1) unite(j, l);
			l = j;
		}
	}

	ll res = 0, part = 0;

	for(int i=0; i<n; ++i) if(root[i] < 0){
		res -= root[i] * part;
		part -= root[i];
	}

	std::cout << res << '\n';
}
