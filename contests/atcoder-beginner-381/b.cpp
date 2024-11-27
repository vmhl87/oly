#include <iostream>
#include <string>

int count[300];

int main(){
	std::string s; std::cin >> s;
	int n = s.length();

	if(n&1) goto done;

	for(int i=0; i<n; i+=2) if(s[i] != s[i+1]) goto done;

	for(char c : s) ++count[c];

	for(int i=0; i<300; ++i) if(count[i] != 0 && count[i] != 2)
		goto done;

	std::cout << "Yes\n", exit(0);

done:
	std::cout << "No\n";
}
