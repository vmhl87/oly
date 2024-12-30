#include <iostream>
#include <string>
#include <array>

struct trie{
	trie *next[26];
};

trie root;

int main(){
	std::string s, t; std::cin >> s >> t;

	for(int i=0; i<s.length(); ++i){
		trie *p = &root;
		for(int j=i; j<s.length(); ++j){
			if(!p->next[s[j]-'a'])
				p->next[s[j]-'a'] = new trie;
			p = p->next[s[j]-'a'];
		}
	}

	std::array<int, 2> res = {0, 0};

	for(int i=0; i<t.length(); ++i){
		std::array<int, 2> s = {0, i};
		trie *p = &root;

		for(int j=i; j<t.length(); ++j){
			if(p->next[t[j]-'a']) ++s[0];
			else break;
			p = p->next[t[j]-'a'];
		}

		res = std::max(res, s);
	}

	if(res[0]){
		for(int i=0; i<res[0]; ++i)
			std::cout << t[i+res[1]];
		std::cout << '\n';
	}
}
