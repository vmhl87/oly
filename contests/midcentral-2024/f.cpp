#include <iostream>
#include <string>

std::string b, c = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
	"!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ ",
	e[] = {":)", ":-)", ":-(", ";-)", "xD", "^_^", "-_-", "^o^", "^^;", "(..)"};
char a[110];

bool match(char *i, std::string z){
	for(char j : z) if(*(i++) != j) return 0;
	return 1;
}

int len(char x, char y){
	char *p = a;
	for(char i : b) *(p++) = i;

	for(int i=0; i<110; ++i)
		if(a[i] == x) a[i] = y;

	int res = 0;

	for(char *i=a; i-a<b.length(); ++i){
		for(std::string z : e) if(match(i, z)){
			i += z.length()-1;
			break;
		}

		++res;
	}

	return res;
}

int main(){
	std::getline(std::cin, b);

	int l = len('0', '0'), r = l;

	for(char x : c) for(char y : c) if(x != y){
		int d = len(x, y);
		l = std::min(l, d);
		r = std::max(r, d);
	}

	std::cout << l << ' ' << r << '\n';
}
