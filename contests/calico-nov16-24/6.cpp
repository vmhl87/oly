#include <iostream>
#include <numeric>

int next[60000], prev[60000], mem[60000], pf[60000];
bool v[60000];

void test(){
	int n; std::cin >> n;

	int i=1;
	for(int j=65536; j; j/=2)
		if(i+j < 6e4 && pf[i+j] < n)
			i += j;

	n -= pf[i++];

	if(!(--n)){
		std::cout << 1 << ' ' << i-1 << '\n';
		return;
	}

	/*
	for(int i=2; n; ++i){
		int part = mem[i];
		if(n > part){
			n -= part;
			continue;
		}
		*/
	for(int j=0; j<=i; ++j) v[j] = 1;
	for(int j=2; j<=i; ++j) if(v[j]){
		if(i%j){
			if(!(--n)){
				std::cout << j << ' ' << i-j << '\n';
				return;
			}
		}else for(int k=j; k<=i; k+=j) v[k] = 0;
	}
	/*
	for(int j=0; j<=i; ++j)
		next[j] = j+1, prev[j] = j-1, v[j] = 1;
	for(int j=1; j<=i; j=next[j]) if(v[j]){
		if(i%j != 0 || j == 1){
			if(!(--n)){
				std::cout << j << ' ' << i-j << '\n';
				return;
			}
		}else for(int k=j; k<=i; k+=j) if(v[k]){
			next[prev[k]] = next[k];
			prev[next[k]] = prev[k];
			v[k] = 0;
		}
	}
	*/
	/*
	for(int j=1; j<i; ++j)
		if(std::gcd(j, i) == 1)
			if(!(--n)){
				std::cout << j << ' ' << i-j << '\n';
				return;
			}
	*/
}

int main(){
	mem[1] = 1;

	for(int i=2; i<6e4; ++i)
		for(int j=2, k=i; j<=k; ++j)
			if(k%j == 0){
				int part = 1;
				while(k%j == 0) k /= j, part *= j;
				part = (part/j) * (j-1);
				mem[i] = part * mem[k];
				break;
			}

	for(int i=2; i<6e4; ++i)
		pf[i] = pf[i-1] + mem[i];

	int t; std::cin >> t;
	while(t--) test();
}
