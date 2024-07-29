#include <iostream>
#include <string>

void test_case(){
	std::string a, b;
	std::cin >> a >> b;

	int max = 0;

	for(int i=0; i<b.length(); ++i){
		int overlap = 0, j = i;

		for(char c : a){
			if(c == b[j]) ++overlap, ++j;
			if(j == b.length()) break;
		}

		if(overlap > max) max = overlap;
	}

	std::cout << a.length() + b.length() - max << '\n';
}

int main(){
	int n; std::cin >> n;

	while(n--) test_case();
}
