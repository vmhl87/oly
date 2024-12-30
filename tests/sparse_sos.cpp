// [XXX] this doesn't actually work. it has an O(nq) blowup case.

/* Task:
 *
 * Given 1 <= n <= 2e5 (not necessarily distinct) bit-strings of length
 * 1 <= l <= 30, denoted a_1, a_2, a_3, ..., a_n , answer 1 <= q <= 2e5
 * queries of the form: For some bit-string b_i of length l, report the
 * number of elements a_j that are subsets of b_i.
 *
 * Input format:
 *
 * Line 1: n, q, l
 * Line 2: a_1, a_2, a_3, ...
 * Line i+2: b_i
 *
 * Sample input:
 *
 * 4 4 3
 * 010 110 101 100
 * 111
 * 000
 * 110
 * 101
 *
 * Sample output:
 *
 * 4
 * 0
 * 3
 * 2
 *
 */

#include <algorithm>
#include <iostream>
#include <array>

const int N = 2e5;

std::array<int, 2> *level[31];
int sz[31], str[N];

struct trie{
	trie *next[2];
	int res;
};

trie root;
int *res[N];

void dfs(trie *p, int d, int s){
	if(!s) p->res = level[d][0][1];
	else{
		if(p->next[0]){
			sz[d+1] = 0;
			for(int i=0; i<sz[d] && !(level[d][i][0]&s); ++i)
				level[d+1][sz[d+1]++] = level[d][i];
			dfs(p->next[0], d+1, s/2);
		}
		if(p->next[1]){
			int m = 0;
			for(; m<sz[d] && !(level[d][m][0]&s); ++m);
			sz[d+1] = 0;
			int p1 = 0, p2 = m;
			while(p1 < m && p2 < sz[d]){
				if(level[d][p1][0] == (level[d][p2][0]^s))
					level[d+1][sz[d+1]++] = {
						level[d][p1][0],
						level[d][p1][1] + level[d][p2][1]
					}, ++p1, ++p2;
				else if(level[d][p1][0] < (level[d][p2][0]^s))
					level[d+1][sz[d+1]++] = level[d][p1++];
				else level[d+1][sz[d+1]++] = {
					level[d][p2][0]^s,
					level[d][p2++][1]
				};
			}
			while(p1 < m)
				level[d+1][sz[d+1]++] = level[d][p1++];
			while(p2 < sz[d])
				level[d+1][sz[d+1]++] = level[d][p2++];
			dfs(p->next[1], d+1, s/2);
		}
	}
}

int main(){
	int n, q, l; std::cin >> n >> q >> l;

	for(int i=0; i<=l; ++i)
		level[i] = new std::array<int, 2>[std::min(n, 1<<(l-i))];

	for(int i=0; i<n; ++i)
		for(int j=0; j<l; ++j){
			char c; std::cin >> c;
			str[i] = str[i]*2 + c-'0';
		}

	std::sort(str, str+n);

	for(int i=0; i<n; ++i){
		if(sz[0] && level[0][sz[0]-1][0] == str[i])
			++level[0][sz[0]-1][1];
		else level[0][sz[0]++] = {str[i], 1};
	}

	for(int i=0; i<q; ++i){
		trie *p = &root;
		for(int j=0; j<l; ++j){
			char c; std::cin >> c;
			if(!p->next[c-'0']) p->next[c-'0'] = new trie;
			p = p->next[c-'0'];
		}
		res[i] = &(p->res);
		p->res = -1;
	}

	dfs(&root, 0, 1<<(l-1));

	for(int i=0; i<q; ++i)
		std::cout << res[i][0] << '\n';
}
