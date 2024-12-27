#include <iostream>

int *a[21], d[1<<21];

int r[1000000];

struct trie{
	int next[3], res;
};

trie seq[10000000];
int nxt = 0;

int b[1000000];

void dfs(int p, int d, int s){
	if(s == 1)
		while(seq[p].res)
			b[seq[p].res-1] = a[d][0],
			seq[p].res = r[seq[p].res-1];
	else{
		if(seq[p].next[0]){
			for(int i=0; i<s/2; ++i)
				a[d+1][i] = a[d][i];
			dfs(seq[p].next[0], d+1, s/2);
		}
		if(seq[p].next[1]){
			for(int i=0; i<s/2; ++i)
				a[d+1][i] = a[d][i+s/2];
			dfs(seq[p].next[1], d+1, s/2);
		}
		if(seq[p].next[2]){
			for(int i=0; i<s/2; ++i)
				a[d+1][i] = a[d][i+s/2];
			for(int i=0; i<s/2; ++i)
				a[d+1][i] += a[d][i];
			dfs(seq[p].next[2], d+1, s/2);
		}
	}
}

int main(){
	std::cin.tie(0) -> sync_with_stdio(0);

	int l, q; std::cin >> l >> q;

	a[0] = d;
	for(int s=1<<l, p=1; s; ++p, s/=2)
		a[p] = a[p-1]+s;

	for(int i=0; i<1<<l; ++i){
		char c; std::cin >> c;
		a[0][i] = c-'0';
	}

	for(int i=0; i<q; ++i){
		int p = 0;
		for(int j=0; j<l; ++j){
			char c; std::cin >> c;
			int r = c == '?' ? 2 : c - '0';
			if(!seq[p].next[r]) seq[p].next[r] = ++nxt;
			p = seq[p].next[r];
		}
		r[i] = seq[p].res;
		seq[p].res = i+1;
	}

	dfs(0, 0, 1<<l);

	for(int i=0; i<q; ++i) std::cout << b[i] << " \n"[i==q-1];
}
