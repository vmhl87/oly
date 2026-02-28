#include <iostream>
#include <string>

char a[26], b[26], z[26];

void rotate(char *a, int m){  // rotate_to
	m = (26+(m%26))%26;
	for(int i=0; i<26; ++i) z[i] = a[(i+m)%26];
	for(int i=0; i<26; ++i) a[i] = z[i];
}

void run(char c){
	if(c == ' '){
		std::cout << c;
		return;
	}

	int index = 0;
	for(int i=1; i<26; ++i) if(a[i] == c) index = i;

	rotate(a, index), rotate(b, -index);

	std::cout << b[0];

	char x = a[25];
	for(int i=25; i>13; --i) a[i] = a[i-1];
	a[13] = x;

	rotate(b, 1);

	x = b[2];
	for(int i=2; i<13; ++i) b[i] = b[i+1];
	b[13] = x;
}

void test(){
	std::string s;

	std::getline(std::cin, s);
	for(int i=0; i<26; ++i) a[i] = s[i];

	std::getline(std::cin, s);
	for(int i=0; i<26; ++i) b[i] = s[i];

	std::getline(std::cin, s);
	for(char c : s) run(c);
	std::cout << '\n';
}

int main(){
	int t; std::cin >> t;
	std::string s; std::getline(std::cin, s);
	while(t--) test();
}
