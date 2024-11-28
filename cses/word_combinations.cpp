#include <iostream>
#include <string>

using ll = long long;
const int m = 1e9 + 7;

struct trie{
	trie *next[26];
	int count;
};

trie root;

std::string s;
int n;

bool v[5000];
ll dp[5000];

ll f(int i){
	if(i == s.length()) return 1;

	if(v[i]) return dp[i];
	v[i] = 1;

	trie *p = &root;
	for(int j=i; j<s.length(); ++j){
		if(!p->next[s[j]-'a']) break;
		p = p->next[s[j]-'a'];
		
		if(p->count)
			dp[i] += p->count*f(j+1) % m;
	}

	return dp[i] %= m;
}

int main(){
	std::cin >> s >> n;

	for(int i=0; i<n; ++i){
		std::string a; std::cin >> a;
		trie *p = &root;

		for(char c : a){
			int v = c-'a';
			if(!p->next[v]) p->next[v] = new trie{};
			p = p->next[v];
		}

		++(p->count);
	}

	std::cout << f(0) << '\n';
}
