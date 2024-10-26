#include <iostream>
#include <string>

struct trie{
	int minlen = 0;
	trie *next[26] = {};
};

trie root;

int main(){
	int n; std::cin >> n;

	while(n--){
		std::string s; std::cin >> s;

		trie *now = &root;

		// matches root -> traverse along until no avail
		int i, best = s.length();
		for(i=0; i<s.length(); ++i){
			if(now -> next[s[i]-'a'] != 0){
				now = now -> next[s[i]-'a'];
				best = std::min(best, (int)s.length() - i + (now -> minlen) - i - 2);
				now -> minlen = std::min(now -> minlen, (int)s.length());
			}else break;
		}

		std::cout << best << '\n';

		// build up trie
		for(; i<s.length(); ++i){
			now -> next[s[i]-'a'] = new trie;
			now = now -> next[s[i]-'a'];
			now -> minlen = s.length();
		}
	}
}
