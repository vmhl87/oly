#include <iostream>
#include <string>

using ll = long long;

ll count[26], pair[26][26];

int main(){
	std::string s; std::cin >> s;

	ll res = 0;

	for(char x : s){
		int v = x - 'A';
		for(int i=0; i<26; ++i)
			res += pair[v][i];
		for(int i=0; i<26; ++i)
			pair[i][v] += count[i];
		++count[v];
	}

	std::cout << res << '\n';
}
